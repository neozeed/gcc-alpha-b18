/* fhandler.cc.  See console.cc for fhandler_console functions.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "winsup.h"

static NO_COPY const int CHUNK_SIZE = 1024; /* Used for crlf conversions */

uid_t
get_file_owner (char *filename)
{
  if (get_os_type () == winNT)
    {
      char psd_buffer[1024];
      PSECURITY_DESCRIPTOR psd = (PSECURITY_DESCRIPTOR) psd_buffer;
      DWORD requested_length;
      PSID psid;
      BOOL bOwnerDefaulted = TRUE;

      if (!GetFileSecurity (filename, OWNER_SECURITY_INFORMATION,
			   psd, 1024, &requested_length))
        return getuid();

      if (!GetSecurityDescriptorOwner (psd, &psid, &bOwnerDefaulted))
        return getuid ();

      return psid ? get_id_from_sid (psid) : getuid ();
    }

  return getuid();
}

gid_t
get_file_group (char *filename)
{
  if (get_os_type () == winNT)
    {
      char psd_buffer[1024];
      PSECURITY_DESCRIPTOR psd = (PSECURITY_DESCRIPTOR) psd_buffer;
      DWORD requested_length;
      PSID psid;
      BOOL bGroupDefaulted = TRUE;

      /* obtain the file's group information */
      if (!GetFileSecurity (filename, GROUP_SECURITY_INFORMATION, psd,
			    1024, &requested_length))
        return getgid();

      /* extract the group sid from the security descriptor */
      if(!GetSecurityDescriptorGroup (psd, &psid, &bGroupDefaulted))
        return getgid ();

      return psid ? get_id_from_sid (psid) : getuid ();
    }

  return getgid ();
}

void
hinfo::clearout (void)
{
  h = 0;
}

int
fhandler_make_pipe (int fildes[2])
{
  int  fdr, fdw;
  fdr = myself->hmap.find_unused_handle (0);
  if (fdr < 0) 
    set_errno (ENMFILE);
  else 
    {
      fdw = myself->hmap.find_unused_handle (fdr+1);
      if (fdw < 0)
	set_errno ( ENMFILE);
      else
	{
	  SECURITY_ATTRIBUTES sa;

	  sa.nLength = sizeof (sa);
	  sa.lpSecurityDescriptor = 0;

	  /* When we fork we duplicate all the file handles to be inherited,
	     therefore all fds must be created as non-inheritable if we're the
	     parent.  We still set the close-on-exec flag to "no" though. */
	  /* FIXME: This comment is out of date.  Gee, what a surprise.  */

	  sa.bInheritHandle = 1;
	  HANDLE r, w;
	  if (CreatePipe (&r, &w, &sa, 0))
	    {
	      myself->hmap.build_fhandler ("piper", fdr, r);
	      myself->hmap.build_fhandler ("pipew", fdw, w);
	      
	      ((fhandler_base *) myself->hmap[fdr].h)->init (r, 1, GENERIC_READ, "piper");
	      ((fhandler_base *) myself->hmap[fdw].h)->init (w, 1, GENERIC_WRITE, "pipew");

	      fildes[0] = fdr;
	      fildes[1] = fdw;
	      
	      debug_printf ("0 = pipe (%d) (%d:%d, %d:%d)\n",
			    fildes, 
			    fdr, 
			    myself->hmap[fdr].h->get_handle (),
			    fdw,
			    myself->hmap[fdw].h->get_handle ());

	      return 0;
	    }
	  else
	    {
	      __seterrno ();
	    }
	}
    }
  
  syscall_printf ("-1 = pipe (0x%x)\n", fildes);
  return -1;
}

/**********************************************************************/
/* fhandler_base */

/* Record the file name.
   Filenames are used mostly for debugging messages, and it's hoped that
   in cases where the name is really required, the filename wouldn't ever
   be too long (e.g. devices or some such).
*/

void
fhandler_base::set_name (const char *p)
{
  if (unix_path_name_ != 0)
    {
      delete [] unix_path_name_;
    }

  if (p == 0)
    {
      unix_path_name_ = 0;
      return;
    }

  unix_path_name_ = new char [ strlen(p) + 1 ];
  if (unix_path_name_ == 0)
    {
      small_printf ("fhandler_base::set_name - fatal error. New failed\n");
      exit (ENOMEM);
    }
  strcpy (unix_path_name_, p);
}

/* Normal file i/o handlers.  */

/* Cover function to ReadFile to achieve (as much as possible) Posix style
   semantics and use of errno.  */
int
fhandler_base::raw_read (void *ptr, size_t ulen)
{
  DWORD bytes_read;
  int len = ulen;

  if (!ReadFile (get_handle(), ptr, len, &bytes_read, 0))
    {
      int errcode;

      /* Some errors are not really errors.  Detect such cases here.  */

      errcode = GetLastError ();
      switch (errcode)
	{
	case ERROR_BROKEN_PIPE:
	  /* This is really EOF.  */
	  bytes_read = 0;
	  break;
	case ERROR_MORE_DATA:
	  /* `bytes_read' is supposedly valid.  */
	  break;
	default:
	  syscall_printf ("ReadFile %s failed\n", unix_path_name_);
	  set_errno (EACCES);
	  return -1;
	  break;
	}
    }

  return bytes_read;
}

int
fhandler_base::linearize (unsigned char *buf)
{
  int len = (sizeof (access_) + sizeof (handle_) + sizeof (w_binary_) +
            sizeof (r_binary_) + sizeof (close_exec_p_) +
            sizeof (readahead_valid_) + sizeof (readahead_) +
            sizeof (append_p_) + sizeof (rpos_) + sizeof (rsize_) +
            sizeof (had_eof_) + sizeof (symlink_p_) + sizeof (execable_p_) +
            sizeof (namehash_) + sizeof (async_) + sizeof (openflags_));
  
  if (buf == 0)
    return len;

  memcpy (buf, (char *) &access_, sizeof (access_));
  buf += sizeof (access_);
  memcpy (buf, (char *) &handle_, sizeof (handle_));
  buf += sizeof (handle_);
  memcpy (buf, (char *) &w_binary_, sizeof (w_binary_));
  buf += sizeof (w_binary_);
  memcpy (buf, (char *) &r_binary_, sizeof (r_binary_));
  buf += sizeof (r_binary_);
  memcpy (buf, (char *) &close_exec_p_, sizeof (close_exec_p_));
  buf += sizeof (close_exec_p_);
  memcpy (buf, (char *) &readahead_valid_, sizeof (readahead_valid_));
  buf += sizeof (readahead_valid_);
  memcpy (buf, (char *) &readahead_, sizeof (readahead_));
  buf += sizeof (readahead_);
  memcpy (buf, (char *) &append_p_, sizeof (append_p_));
  buf += sizeof (append_p_);
  memcpy (buf, (char *) &rpos_, sizeof (rpos_));
  buf += sizeof (rpos_);
  memcpy (buf, (char *) &rsize_, sizeof (rsize_));
  buf += sizeof (rsize_);
  memcpy (buf, (char *) &had_eof_, sizeof (had_eof_));
  buf += sizeof (had_eof_);
  memcpy (buf, (char *) &symlink_p_, sizeof (symlink_p_));
  buf += sizeof (symlink_p_);
  memcpy (buf, (char *) &execable_p_, sizeof (execable_p_));
  buf += sizeof (execable_p_);
  memcpy (buf, (char *) &namehash_, sizeof (namehash_));
  buf += sizeof (namehash_);
  memcpy (buf, (char *) &async_, sizeof (async_));
  buf += sizeof (async_);
  memcpy (buf, (char *) &openflags_, sizeof (openflags_));
  buf += sizeof (openflags_);
  
  return len;
}

int
fhandler_base::de_linearize (const unsigned char *buf)
{
  const unsigned char *orig_buf = buf;

  memcpy ((char *) &access_, buf, sizeof (access_));
  buf += sizeof (access_);
  memcpy ((char *) &handle_, buf, sizeof (handle_));
  buf += sizeof (handle_);
  memcpy ((char *) &w_binary_, buf, sizeof (w_binary_));
  buf += sizeof (w_binary_);
  memcpy ((char *) &r_binary_, buf, sizeof (r_binary_));
  buf += sizeof (r_binary_);
  memcpy ((char *) &close_exec_p_, buf, sizeof (close_exec_p_));
  buf += sizeof (close_exec_p_);
  memcpy ((char *) &readahead_valid_, buf, sizeof (readahead_valid_));
  buf += sizeof (readahead_valid_);
  memcpy ((char *) &readahead_, buf, sizeof (readahead_));
  buf += sizeof (readahead_);
  memcpy ((char *) &append_p_, buf, sizeof (append_p_));
  buf += sizeof (append_p_);
  memcpy ((char *) &rpos_, buf, sizeof (rpos_));
  buf += sizeof (rpos_);
  memcpy ((char *) &rsize_, buf, sizeof (rsize_));
  buf += sizeof (rsize_);
  memcpy ((char *) &had_eof_, buf, sizeof (had_eof_));
  buf += sizeof (had_eof_);
  memcpy ((char *) &symlink_p_, buf, sizeof (symlink_p_));
  buf += sizeof (symlink_p_);
  memcpy ((char *) &execable_p_, buf, sizeof (execable_p_));
  buf += sizeof (execable_p_);
  memcpy ((char *) &namehash_, buf, sizeof (namehash_));
  buf += sizeof (namehash_);
  memcpy ((char *) &async_, buf, sizeof (async_));
  buf += sizeof (async_);
  memcpy ((char *) &openflags_, buf, sizeof (openflags_));
  buf += sizeof (openflags_);
  
  return buf - orig_buf;
}

/* Cover function to WriteFile to provide Posix interface and semantics
   (as much as possible).  */
int
fhandler_base::raw_write (const void *ptr, size_t len)
{
  DWORD bytes_written;

  if (!WriteFile (get_handle(), ptr, len, &bytes_written, 0))
    {
      __seterrno ();
      if (get_errno () == EPIPE)
        raise (SIGPIPE);
      return -1;
    }
  return bytes_written;
}

/* Open system call handler function.
   Path is now already checked for symlinks */
fhandler_base * 
fhandler_base::open (const char *path, int flags, mode_t mode)
{
  fhandler_base * res = NULL;
  HANDLE x;
  int file_attributes;
  int shared;
  SECURITY_ATTRIBUTES sa;
  int creation_distribution;

  syscall_printf ("(%s, 0x%x)\n", path, flags);

  set_flags (flags);
  path_conv win32_path (path, -1);
  if (win32_path.error)
    {
      set_errno (win32_path.error);
      goto done;
    }

  if ((flags & (O_RDONLY | O_WRONLY | O_RDWR)) == O_RDONLY)
    {
      access_ = GENERIC_READ;
    }
  else if ((flags & (O_RDONLY | O_WRONLY | O_RDWR)) == O_WRONLY)
    {
      access_ = GENERIC_WRITE;
    }
  else
    {
      access_ = GENERIC_READ | GENERIC_WRITE;
    }

  /* FIXME: O_EXCL handling?  */

  if ((flags & O_TRUNC) && ((flags & O_ACCMODE) != O_RDONLY))
    {
      if (flags & O_CREAT)
        {
          creation_distribution = CREATE_ALWAYS;
        }
      else
        {
          creation_distribution = TRUNCATE_EXISTING;
        }
    }
  else
    {
      if (flags & O_CREAT)
        {
          creation_distribution = OPEN_ALWAYS;
        }
      else
        {
          creation_distribution = OPEN_EXISTING;
        }
    }

  if ((flags & O_EXCL) && (flags & O_CREAT))
    {
      creation_distribution = CREATE_NEW;
    }

  if (flags & O_APPEND) 
    {
      append_p_ = 1;
    }

  /* These flags are host dependent. */
  shared = host_dependent.shared;

  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = 0;

  sa.bInheritHandle = TRUE;
  file_attributes = FILE_ATTRIBUTE_NORMAL;
  if (flags & O_DIROPEN)
    file_attributes |= FILE_FLAG_BACKUP_SEMANTICS;

  x = CreateFileA (win32_path.get_win32 (), access_, shared,
		   &sa, creation_distribution,
		   file_attributes,
		   0);

  syscall_printf ("%d = CreateFileA (%s, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0)\n",
		  x,
		  win32_path.get_win32 (), access_, shared,
		  &sa, creation_distribution,
		  file_attributes);
	
  if (x == INVALID_HANDLE_VALUE)
    {
      if (GetLastError () == ERROR_INVALID_HANDLE)
	set_errno (ENOENT);
      else
	__seterrno ();
      goto done;
    }

  if (flags & O_CREAT)
    {
      set_file_attribute (win32_path.get_win32 (), mode);
    }
  set_name (path);
  namehash_ = hash_path_name (0, win32_path.get_win32 ());
  set_handle (x);
  readahead_valid_ = 0;
  set_close_on_exec (0);
  symlink_p_ = 0;
  execable_p_ = 0;
  rpos_ = 0;
  had_eof_ = 0;
  rsize_ = -1;

  if (win32_path.binary_p || (flags & O_BINARY))
    {
      set_r_binary (1);
      set_w_binary (1);
    }
  else if (flags & O_TEXT)
    {
      set_r_binary (0);
      set_w_binary (0);
    }
  else if (u->fmode_ptr && (*(u->fmode_ptr) & O_BINARY))
    {
      set_r_binary (1);
      set_w_binary (1);
      syscall_printf ("filemode defaulting to binary.\n");
    }
  else 
    {
      set_r_binary (0);
      set_w_binary (0);
      syscall_printf ("filemode defaulting to text.\n");
    }

  if (flags & O_APPEND)
    SetFilePointer (get_handle(), 0, 0, FILE_END);
  else
    SetFilePointer (get_handle(), 0, 0, FILE_BEGIN);

  res = this;
done:
  syscall_printf ("%p = fhandler_base::open (%s, 0x%x)\n", res, path, flags);
  return res;
}

/* states:
   open buffer in binary mode?  Just do the read.  

   open buffer in text mode?  Scan buffer for control zs and handle
   the first one found.  Then scan buffer, converting every \r\n into
   an \n.  If last char is an \r, look ahead one more char, if \n then
   modify \r, if not, remember char.  
*/
int
fhandler_base::read (void *ptr, size_t ulen)
{
  int len = ulen;
  char *ctrlzpos;
  int i;

  if (len == 0)
    return 0;

  if (get_r_binary ())
    {
      int l = raw_read (ptr, len);
      if (l <= 0)
	return l;
      rpos_ += l;
      return l;
    }

  int chars_to_process;
  /* We're in text mode */
  if (readahead_valid_)
    {
      /* We have one character to consume from the last read. */
      readahead_valid_ = 0;
      ((char *) ptr)[0] = readahead_;
      chars_to_process = raw_read (&(((char *) ptr)[1]), len - 1);
      if (chars_to_process < 0)
        return chars_to_process;
      else if (chars_to_process == 0)
	{
	/* Even if raw_read returned 0 we still have the 
	  readahead char to process */
	  chars_to_process = 1; 
	}
      else
	{
	  /* We must increment chars_to_process
          as we already had the readahead char */
          chars_to_process += 1;
        }
    }
  else
    {
      chars_to_process = raw_read (ptr, len);
      if (chars_to_process <= 0)
        return chars_to_process;
    }

  /* If the first character is a control-z we're at virtual EOF.  */
  if (((char *) ptr)[0] == 0x1a)
    {
      return 0;
    }

  /* Scan buffer for a control-z and shorten the buffer to that length */

  ctrlzpos = (char *) memchr ((char *) ptr, 0x1a, chars_to_process);
  if (ctrlzpos)
    {	
      lseek ((ctrlzpos - ((char *) ptr + chars_to_process)), SEEK_CUR);
      chars_to_process = ctrlzpos - (char *) ptr;
    }

  /* Scan buffer and turn \r\n into \n */
  register char *src= (char *) ptr;
  register char *dst = (char *) ptr;
  register char *end = src + chars_to_process - 1;

  /* Read up to the last but one char - the last char needs special handling */
  while (src < end)
    {
      if (src[0] == '\r' && (src[1] == '\n' || src[1] == '\r'))
	{
	  /* Ignore this. */
	  src++;
	}
      else
	{
	  *dst++ = *src++;
	}
    }

  /* if last char is a '\r' then read one more to see if we should
     translate this one too */
  if (*src == '\r')
    {
      int len;
      char c;
      len = raw_read (&c, 1);
      if (len > 0)
	{
	  if (c == '\n')
	    {
	      *dst++ = '\n';
	    }
	  else
	    {
	      readahead_valid_ = 1;
	      readahead_ = c;
	    }
	}
    }
  else
    {
      *dst++ = *src;
    }

  chars_to_process = dst - (char *) ptr;

  rpos_ += chars_to_process;

  if (myself->strace_mask & (_STRACE_DEBUG | _STRACE_ALL))
    {
      char buf[16 * 6 + 1];
      char *p = buf;

      for (int i = 0; i < chars_to_process && i < 16; ++i)
	{
	  unsigned char c = ((unsigned char *) ptr)[i];
	  /* >= 33 so space prints in hex */
	  __small_sprintf (p, c >= 33 && c <= 127 ? " %c" : " 0x%x", c);
	  p += strlen (p);
	}
      debug_printf ("read %d bytes (%s%s)\n", chars_to_process, buf, chars_to_process > 16 ? " ..." : "");
    }

  return chars_to_process;
}

int
fhandler_base::write (const void *ptr, size_t len)
{
  int res;

  if (append_p_)
    SetFilePointer (get_handle(), 0, 0, FILE_END);

  if (get_w_binary ())
    {
      res = raw_write (ptr, len);
    }
  else
    {
      /* Keep track of previous \rs, we don't want to turn existing
	 \r\n's into \r\n\n's */
      register int pr = 0;

      /* Copy things in chunks */
      char buf[CHUNK_SIZE];

      for (unsigned int i = 0; i < len; i += sizeof (buf) / 2)
	{
	  register const char *src = (char *)ptr + i;
	  int todo = MIN (len - i, sizeof (buf) / 2);
	  register const char *end = src + todo;
	  register char *dst = buf;
	  while (src < end)
	    {
	      if (*src == '\n' && !pr)
		{
		  /* Emit a cr lf here */
		  *dst ++ = '\r';
		  *dst ++ = '\n';
		}
	      else if (*src == '\r')
		{
		  *dst ++ = '\r';
		  pr = 1;
		}
	      else 
		{
		  *dst ++ = *src;
		  pr = 0;
		}
	      src++;
	    }
	  int want = dst - buf;
	  if ((res = raw_write (buf, want)) != want)
	    {
              if (res == -1)
                return -1;
              /* FIXME: */
	      /* Tricky... Didn't write everything we wanted.. How can
		 we work out exactly which chars were sent?  We don't...
		 This will only happen in pretty nasty circumstances. */
	      rpos_ += i;
	      return i;
	    }
	}
      /* Done everything, update by the chars that the user sent */
      rpos_ += len;
      /* Length of file has changed */
      rsize_ = -1;
      res = len;
      debug_printf ("after write, name %s, rpos %d\n", unix_path_name_, rpos_);
    }
  return res;
}

off_t
fhandler_base::lseek (off_t offset, int whence)
{
  off_t res;

  /* Seeks on text files is tough, we rewind and read till we get to the
     right place.  */

  readahead_valid_ = 0;

  debug_printf ("lseek (%s, %d, %d)\n", unix_path_name_, offset, whence);

#if 0	/* lseek has no business messing about with text-mode stuff */

  if (!get_r_binary ())
    {
      int newplace;

      if (whence == 0)
	{
	  newplace = offset;
	}
      else if (whence ==1)
	{
	  newplace = rpos +  offset;
	}
      else 
	{
	  /* Seek from the end of a file.. */
	  if (rsize == -1)
	    {
	      /* Find the size of the file by reading till the end */
	      
	      char b[CHUNK_SIZE];
	      while (read (b, sizeof (b)) > 0)
		;
	      rsize = rpos;
	    }
	  newplace = rsize + offset;
	}

      if (rpos > newplace)
	{
	  SetFilePointer (handle, 0, 0, 0);
	  rpos = 0;
	}

      /* You can never shrink something more than 50% by turning CRLF into LF,
	 so we binary chop looking for the right place */

      while (rpos < newplace)
	{
	  char b[CHUNK_SIZE];
	  size_t span = (newplace - rpos) / 2;
	  if (span == 0)
	    span = 1;
	  if (span > sizeof (b))
	    span = sizeof (b);

	  debug_printf ("lseek (%s, %d, %d) span %d, rpos %d newplace %d\n",
		       name, offset, whence,span,rpos, newplace);
	  read (b, span);
	}

      debug_printf ("Returning %d\n", newplace);
      return newplace;
    }
#endif	/* end of deleted code dealing with text mode */

  DWORD win32_whence = whence == SEEK_SET ? FILE_BEGIN
                       : (whence == SEEK_CUR ? FILE_CURRENT : FILE_END);

  res = SetFilePointer (get_handle(), offset, 0, win32_whence);

  if (res == -1)
    {
      __seterrno ();
    }
  return res;
}

int
fhandler_base::close (void)
{
  int res = -1;

  syscall_printf ("(handle %d)\n",get_handle());

  /* int type = GetFileType (handle);*/
  int type = 0;

  /* Can't really close these things, but pretend we did. */
  if (type == FILE_TYPE_CHAR && 0)
    res = 0;
  else 
    {
      if (!CloseHandle (get_handle()))
	{
	  paranoid_printf ("CloseHandle (%d <%s>) failed\n", get_handle(), unix_path_name_);

	  __seterrno ();
	}
      else
	{
	  if (type == FILE_TYPE_DISK)
	    s->delqueue.process_queue ();
	  res = 0;
	  set_handle ((HANDLE) - 99);
	}
    }
  return res;
}

int
fhandler_base::ioctl (int cmd, void *buf)
{
  if (cmd == FIONBIO)
    {
      syscall_printf ("ioctl (FIONBIO,%x)\n", buf);
    }
  else
    {
      syscall_printf ("ioctl (%x,%x)\n", cmd, buf);
    }

  set_errno (EINVAL);
  return -1;
}

int
fhandler_base::lock (int, struct flock *)
{
  set_errno (ENOSYS);
  return -1;
}

int
fhandler_base::fstat (struct stat *buf)
{
  int res;
  BY_HANDLE_FILE_INFORMATION local;

  memset (buf, 0, sizeof (*buf));

  /* NT 3.5.1 seems to have a bug when attempting to get vol serial
     numbers.  This loop gets around this. */
  for (int i = 0; i < 2; i++)
    {
      if (!(res = GetFileInformationByHandle (get_handle (), &local)))
	break;
      if (local.dwVolumeSerialNumber && (long) local.dwVolumeSerialNumber != -1)
	break;
    }
  debug_printf ("%d = GetFileInformationByHandle (%s, %d)\n",
		res, unix_path_name_, get_handle ());
  if (res == 0)
    {
      /* GetFileInformationByHandle will fail if it's given stdin/out/err 
	 or a pipe*/
      if (1)
	{
	  /* We expect these to fail! */
	  buf->st_mode = S_IFCHR | STD_RBITS | STD_WBITS;
	  buf->st_blksize = S_BLKSIZE;
	  buf->st_ino = namehash_;
	  syscall_printf ("0 = fstat (, 0x%x)\n",  buf);
	  return 0;
	}
      else
	{
	  __seterrno ();
	  syscall_printf ("-1 = fstat (, 0x%x)\n",  buf);
	  return -1;
	}
    }

  path_conv win32_path (get_name (), -1);

  if (win32_path.error)
    {
      set_errno (win32_path.error);
      return -1;
    }
  set_errno (0);

  buf->st_atime   = to_time_t (&local.ftLastAccessTime);
  buf->st_mtime   = to_time_t (&local.ftLastWriteTime);
  buf->st_ctime   = to_time_t (&local.ftCreationTime);
  buf->st_nlink   = local.nNumberOfLinks;
  buf->st_dev     = local.dwVolumeSerialNumber;
  buf->st_size    = local.nFileSizeLow;
  buf->st_ino     = local.nFileIndexLow ^ namehash_;
  buf->st_blksize = S_BLKSIZE;
  buf->st_blocks  = (buf->st_size + S_BLKSIZE-1) / S_BLKSIZE;
  buf->st_uid     = get_file_owner (win32_path.get_win32 ());
  buf->st_gid     = get_file_group (win32_path.get_win32 ());
  if (get_file_attribute (win32_path.get_win32 (), (int *) &buf->st_mode) > 0)
    {
      buf->st_mode &= ~S_IFMT;
      if (symlink_p_)
        buf->st_mode |= S_IFLNK;
      else
        buf->st_mode |= S_IFREG;
    }
  else
    {
      buf->st_mode = 0;
      buf->st_mode |= STD_RBITS;
  
      if (! (local.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
        buf->st_mode |= STD_WBITS;	
      /* | S_IWGRP | S_IWOTH; we don't give write to group etc */

      if (symlink_p_)
        buf->st_mode |= S_IFLNK;
      else
        switch (GetFileType (get_handle ()))
          {
          case FILE_TYPE_CHAR:
          case FILE_TYPE_UNKNOWN:
	    buf->st_mode |= S_IFCHR;
	    break;
          case FILE_TYPE_DISK:
	    buf->st_mode |= S_IFREG;
	    if (execable_p_)
	      buf->st_mode |= STD_XBITS;
	    break;
          case FILE_TYPE_PIPE:
	    buf->st_mode |= S_IFSOCK;
	    break;
          }
    }

  syscall_printf ("0 = fstat (, 0x%x) st_atime=%x st_size=%d, st_mode=0x%x, st_ino=%d, sizeof=%d\n",
		 buf, buf->st_atime, buf->st_size, buf->st_mode, 
		 (int) buf->st_ino, sizeof (*buf));

  return 0;
}

void
fhandler_base::init (HANDLE f, int bin, int a, const char *n)
{
  set_handle (f);
  set_r_binary (bin);
  set_w_binary (bin);
  access_ = a;
  set_name (n);
  a &= GENERIC_READ | GENERIC_WRITE;
  if (a == GENERIC_READ)
    set_flags (O_RDONLY);
  if (a == GENERIC_WRITE)
    set_flags (O_WRONLY);
  if (a == (GENERIC_READ | GENERIC_WRITE))
    set_flags (O_RDWR);
  debug_printf ("created new fhandler_base for <%s> with handle %d\n", n, f);
}

void
fhandler_base::dump (void)
{
  paranoid_printf ( "FHANDLER BASE\n");
}

void
fhandler_base::set_handle (HANDLE x)
{
  debug_printf ("set handle to %d\n", x);
  handle_ = x;
}

int
fhandler_base::dup (fhandler_base *child)
{
  debug_printf ("in fhandler_base dup\n");

  child->set_close_on_exec (0);
#ifndef __alpha
  const HANDLE proc = GetCurrentProcess ();
#else
  HANDLE proc = GetCurrentProcess (); 
#endif
  HANDLE nh;

  if (!DuplicateHandle (proc, get_handle(), proc, &nh, 0, 1,
                                                  DUPLICATE_SAME_ACCESS))
    {
      small_printf ("COPY FOR DUP FAILED, handle in %x %x!!\n",
                                        get_handle(), GetLastError ());
      __seterrno ();
      return -1;
    }

  child->set_handle (nh);
  return 0;
}

/* Base terminal handlers.  These just return errors.  */

int
fhandler_base::tcflush (int queue)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcsendbreak (int duration)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcdrain (void)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcflow (int action)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcsetattr (int a, const struct termios *t)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcgetattr (struct termios *t)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcsetpgrp (const pid_t pid)
{
  set_errno (ENOTTY);
  return -1;
}

int
fhandler_base::tcgetpgrp (void)
{
  set_errno (ENOTTY);
  return -1;
}

/* Normal I/O constructor */
fhandler_base::fhandler_base (const char *name)
{
  w_binary_ = 0;
  r_binary_ = 0;
  close_exec_p_ = 0;
  handle_ = 0; 
  access_ = 0; 
  readahead_valid_ = 0; 
  readahead_ = 0; 
  append_p_ = 0;
  rpos_ = 0;
  rsize_ = 0;
  had_eof_ = 0;
  symlink_p_ = 0;
  namehash_ = 0;
  execable_p_ = 0;
  unix_path_name_ = 0;
  async_ = 0;
  openflags_ = 0;
  set_name (name);
}

/* Normal I/O destructor */
fhandler_base::~fhandler_base (void)
{
  delete [] unix_path_name_;
}

/**********************************************************************/
/* fhandler_disk_file */

fhandler_disk_file::fhandler_disk_file (const char *name) : fhandler_base(name)
{
}

fhandler_base *
fhandler_disk_file::open (const char *path, int flags, mode_t mode)
{
  fhandler_base * res = NULL;

  syscall_printf ("(%s, 0x%x)\n", path, flags);

  /* O_NOSYMLINK is an internal flag for implementing lstat, nothing more. */
  path_conv real_path (path, (flags & O_NOSYMLINK) ? 0 : 1);

  if (real_path.error)
    {
      if (flags & O_NOSYMLINK)
	{
	  set_errno (real_path.error);
	  syscall_printf ("%p = fhandler_disk_file::open (%s, 0x%x)\n",
			  res, path, flags);
	  return res;
	}
      else
	{
	  if (real_path.error != ENOENT || (flags & O_CREAT) == 0)
	    {
	      set_errno (real_path.error);
	      syscall_printf ("%p = fhandler_disk_file::open (%s, 0x%x)\n",
			      res, path, flags);
	      return res;
	    }
	}
    }

  /* If necessary, do various other things to see if path is a program.  */
  if (!real_path.exec_p)
    real_path.exec_p = check_execable_p (real_path.get_win32 ());

  res = this->fhandler_base::open (real_path.get_win32 (), flags, mode);

  symlink_p_ = real_path.symlink_p;
  execable_p_ = real_path.exec_p;

  syscall_printf ("%p = fhandler_disk_file::open (%s, 0x%x)\n", res, path, flags);
  return res;
}

/*
 * FIXME !!!
 * The correct way to do this to get POSIX locking
 * semantics is to keep a linked list of posix lock
 * requests and map them into Win32 locks. The problem
 * is that Win32 does not deal correctly with overlapping
 * lock requests. Also another pain is that Win95 doesn't do
 * non-blocking or non exclusive locks at all. For '95 just
 * convert all lock requests into blocking,exclusive locks.
 * This shouldn't break many apps but denying all locking
 * would.
 * For now just convert to Win32 locks and hope for the best.
 */

int
fhandler_disk_file::lock (int cmd, struct flock *fl)
{
  DWORD win32_start;
  DWORD win32_len;
  DWORD win32_upper;
  DWORD startpos;

  /*
   * We don't do getlck calls yet.
   */

  if (cmd == F_GETLK)
    {
      set_errno (ENOSYS);
      return -1;
    }

  /* 
   * Calculate where in the file to start from,
   * then adjust this by fl->l_start.
   */

  switch (fl->l_whence)
    {
      case SEEK_SET:
        startpos = 0;
        break;
      case SEEK_CUR:
        if ((startpos = lseek (0, SEEK_CUR)) < 0)
          return -1;
        break;
      case SEEK_END:
        {
          BY_HANDLE_FILE_INFORMATION finfo;
          if (GetFileInformationByHandle (get_handle(), &finfo) == 0)
            { 
              __seterrno ();
              return -1;
            }
          startpos = finfo.nFileSizeLow; /* Nowhere to keep high word */
          break;
        }
    }

  /* 
   * Now the fun starts. Adjust the start and length
   *  fields until they make sense.
   */

  win32_start = startpos + fl->l_start;
  if (fl->l_len < 0)
    {
      win32_start -= fl->l_len;
      win32_len = -fl->l_len;
    }
  else
    win32_len = fl->l_len;

  if (win32_start < 0)
    {
      win32_len -= win32_start;
      if (win32_len <= 0)
        {
          /* Failure ! */
          set_errno (EINVAL);
          return -1;
        }
      win32_start = 0;
    }

  /*
   * Special case if len == 0 for POSIX means lock
   * to the end of the entire file (and all future extensions).
   */
  if (win32_len == 0)
    {
      win32_len = 0xffffffff;
      win32_upper = host_dependent.win32_upper;
    }
  else
    win32_upper = 0;

  BOOL res;

  if (get_os_type () == winNT)
    {
      DWORD lock_flags = (cmd == F_SETLK) ? LOCKFILE_FAIL_IMMEDIATELY : 0;
      lock_flags |= (fl->l_type == F_WRLCK) ? LOCKFILE_EXCLUSIVE_LOCK : 0;

      OVERLAPPED ov;

      ov.Internal = 0;
      ov.InternalHigh = 0;
      ov.Offset = win32_start;
      ov.OffsetHigh = 0;
      ov.hEvent = (HANDLE) 0;

      if (fl->l_type == F_UNLCK)
        {
          res = UnlockFileEx (get_handle (), 0, win32_len, win32_upper, &ov);
        }
      else
        {
          res = LockFileEx (get_handle (), lock_flags, 0, win32_len,
							win32_upper, &ov);
          /* Deal with the fail immediately case. */
          /*
           * FIXME !! I think this is the right error to check for
           * but I must admit I haven't checked....
           */
          if ((res == 0) && (lock_flags & LOCKFILE_FAIL_IMMEDIATELY) &&
                            (GetLastError () == ERROR_LOCK_FAILED))
            {
              set_errno (EAGAIN);
              return -1;
            }
        }
    }
  else
    {
      /* Windows 95 -- use primitive lock call */
      if (fl->l_type == F_UNLCK)
        res = UnlockFile (get_handle (), win32_start, 0, win32_len,
							win32_upper);
      else
        res = LockFile (get_handle (), win32_start, 0, win32_len, win32_upper);
    }

  if (res == 0)
    {
      __seterrno ();
      return -1;
    }

  return 0;
}

/* Perform various heuristics on PATH to see if it's a program. */

int
fhandler_disk_file::check_execable_p (const char *path)
{
  int len = strlen (path);
  const char *ch = path + (len > 4 ? len - 4 : len);

  if (strcasecmp (".bat", ch) == 0
      || strcasecmp (".exe", ch) == 0
      || strcasecmp (".com", ch) == 0)
    return 1;

  return 0;
}

/**********************************************************************/
/* fhandler_tty */

fhandler_tty::fhandler_tty (const char *name) : fhandler_base (name)
{
  vmin_ = 0;
  vtime_ = 0;
  pgrp_ = myself->pgid;
}

int 
fhandler_tty::linearize (unsigned char *buf)
{
  int len = sizeof (vmin_) + sizeof (vtime_);
  if (buf == 0)
    {
      len += this->fhandler_base::linearize (buf);
      return len;
    }

  memcpy (buf, (char *) &vmin_, sizeof (vmin_));
  buf += sizeof (vmin_);
  memcpy (buf, (char *) &vtime_, sizeof (vtime_));
  buf += sizeof (vtime_);
 
  len += this->fhandler_base::linearize (buf);
  return len;
}
 
int
fhandler_tty::de_linearize (const unsigned char *buf)
{
  const unsigned char *orig_buf = buf;

  memcpy ((char *) &vmin_, buf, sizeof (vmin_));
  buf += sizeof (vmin_);
  memcpy ((char *) &vtime_, buf, sizeof (vtime_));
  buf += sizeof (vtime_);

  int len = buf - orig_buf;
  return (len + this->fhandler_base::de_linearize (buf));
}
 
int
fhandler_tty::raw_read (void *ptr, size_t ulen)
{
  if (vtime_ || vmin_)
    {
      if (vmin_ == 0)
	ulen = 1;
      else if (vmin_ < ulen)
	ulen = vmin_;
      syscall_printf ("timeout len %d\n", ulen);
    }
  return fhandler_base::raw_read (ptr, ulen);
}

void
fhandler_tty::dump (void)
{
  paranoid_printf ("FHANDLER TTY\n");
}

fhandler_base * 
fhandler_tty::open (const char *path, int flags, mode_t mode)
{
  fhandler_base *res = NULL;
  int temp = 0;
  int access;
  HANDLE myhandle;
  COMMTIMEOUTS to;

  syscall_printf ("fhandler_tty::open (%s, 0x%x, 0x%x )\n",
			path, flags, mode);

  if ((res = fhandler_base::open (path, flags, mode)) == NULL)
    return NULL;

  memset (&to, 0, sizeof (to));

  myhandle = fhandler_base::get_handle ();
  access = fhandler_base::get_access ();
  temp |= (access & (GENERIC_READ | GENERIC_WRITE));

  if (flags & O_NDELAY)		/* non-blocking I/O */
    {
      temp |= _FNDELAY;

      /* probably not necessary */
      if (GetCommTimeouts (myhandle, &to) == 0)
        {
          small_printf ("GetCommTimeout failed\n");
          __seterrno ();
          return NULL;
        }

      to.ReadIntervalTimeout = MAXDWORD;
      to.ReadTotalTimeoutMultiplier = 0;
      to.ReadTotalTimeoutConstant = 0;

      /* Restore vmin_, vtime_ later, leave values alone for now */

      if (SetCommTimeouts (myhandle, &to) == 0)
        {
          small_printf ("SetCommTimeout failed\n");
          __seterrno ();
          return NULL;
        }
    }	/* non-blocking I/O */
  else
    {	/* blocking I/O */
        /* if non-blocking is set, unset it */
      if (access & _FNDELAY)
        {
          if (SetCommTimeouts (myhandle, &to) == 0)
            {
              small_printf ("SetCommTimeout failed\n");
              __seterrno ();
              return NULL;
            }
        }	/* if non-blocking is set */
    }		/* blocking I/O */

  fhandler_base::set_access (temp);

#if 0
  /* FIXME: does this do the right thing? */
  /* Reset serial port to known state of 9600-8-1-no flow control
     on open for better behavior under Win 95. */
  {
    DCB state;
    BOOL dropDTR = TRUE;
    state.BaudRate = CBR_9600;
    state.ByteSize = 8;
    state.StopBits = ONESTOPBIT;
    state.Parity = NOPARITY; /* FIXME: correct default? */
    state.fBinary = TRUE; /* binary xfer */
    state.EofChar = 0; /* no end-of-data in binary mode */
    state.fNull = FALSE; /* don't discard nulls in binary mode */
    state.fParity = FALSE; /* ignore parity errors */
    state.fErrorChar = FALSE;
    state.fTXContinueOnXoff = TRUE; /* separate TX and RX flow control */
    state.fOutX = FALSE; /* disable transmission flow control */
    state.fInX = FALSE; /* disable reception flow control */
    state.XonChar = 0x11;
    state.XoffChar = 0x13;
    state.fOutxDsrFlow = FALSE; /* disable DSR flow control */
    state.fRtsControl = RTS_CONTROL_DISABLE; /* ignore lead control except
						DTR */
    state.fOutxCtsFlow = FALSE; /* disable output flow control */
    state.fDtrControl = DTR_CONTROL_ENABLE; /* assert DTR */
    state.fDsrSensitivity = FALSE; /* don't assert DSR */
    state.fAbortOnError = FALSE;
    SetCommState (get_handle (), &state);
  }
#endif

  syscall_printf ("%p = fhandler_tty::open (%s, 0x%x, 0x%x)\n",
			res, path, flags, mode);
  return res;
}

int
fhandler_tty::fstat (struct stat *buf)
{
  memset (buf, 0, sizeof (*buf));
  buf->st_mode |= S_IFCHR;
  buf->st_blksize = S_BLKSIZE;
  buf->st_uid     = getuid ();
  buf->st_gid     = getgid ();
  buf->st_mode |= STD_RBITS | STD_WBITS;
  buf->st_ino = get_namehash ();
  syscall_printf ("0 = fhandler_tty:fstat (%x) (mode %x)\n",
		  buf, buf->st_mode);
  return 0;
}

/* tcsendbreak: POSIX 7.2.2.1 */
/* Break for 250-500 milliseconds if duration == 0 */
/* Otherwise, units for duration are undefined */
int
fhandler_tty::tcsendbreak (int duration)
{
  unsigned int sleeptime = 300;

  if (duration > 0)
    sleeptime *= duration;

  if (SetCommBreak (get_handle ()) == 0)
    return -1;

  /* FIXME: need to send zero bits during duration */
  usleep (sleeptime);

  if (ClearCommBreak (get_handle ()) == 0)
    return -1;

  syscall_printf ("0 = fhandler_tty:tcsendbreak (%d)\n", duration);

  return 0;
}

/* tcdrain: POSIX 7.2.2.1 */
int
fhandler_tty::tcdrain (void)
{
  if (FlushFileBuffers (get_handle ()) == 0)
    return -1;

  return 0;
}

/* tcflow: POSIX 7.2.2.1 */
int
fhandler_tty::tcflow (int action)
{
  DWORD win32action = 0;
  DCB dcb;
  char xchar;

  switch (action)
    {
      case TCOOFF:
        win32action = SETXOFF;
        break;
      case TCOON:
        win32action = SETXON;
        break;
      case TCION:
      case TCIOFF:
        if (GetCommState (get_handle (), &dcb) == 0)
          return -1;
        if (action == TCION)
          xchar = (dcb.XonChar ? dcb.XonChar : 0x11);
        else
          xchar = (dcb.XoffChar ? dcb.XoffChar : 0x13);
        if (TransmitCommChar (get_handle (), xchar) == 0)
          return -1;
        return 0;
        break;
      default:
        return -1;
        break;
    }

  if (EscapeCommFunction (get_handle (), win32action) == 0)
    return -1;

  return 0;
}

/* tcflush: POSIX 7.2.2.1 */
int
fhandler_tty::tcflush (int queue)
{
  if (queue & (TCOFLUSH | TCIOFLUSH))
    {
      PurgeComm (get_handle (), PURGE_TXABORT | PURGE_TXCLEAR);
    }

  if (queue & (TCIFLUSH | TCIOFLUSH))
    {
      /* Input flushing by polling until nothing turns up
	 (we stop after 1000 chars anyway) */
      COMMTIMEOUTS old;
      COMMTIMEOUTS tmp;
      char b;
      DWORD more = 1;
      int max = 1000;

      PurgeComm (get_handle (), PURGE_RXABORT | PURGE_RXCLEAR);
      GetCommTimeouts (get_handle (), &old);
      memset (&tmp, 0, sizeof (tmp));
      tmp.ReadTotalTimeoutConstant = 100;
      SetCommTimeouts (get_handle (), &tmp);

      while (max > 0 && more)
	{
	  ReadFile (get_handle (), &b, 1,  &more,  0);
	  if (more) 
	    termios_printf ("dropping %d\n", b);
	  max--;
	}
      SetCommTimeouts (get_handle (), &old);
    }

  return 0;
}

/* tcsetattr: POSIX 7.2.1.1 */
int
fhandler_tty::tcsetattr (int action, const struct termios *t)
{
  /* Possible actions:
    TCSANOW:   immediately change attributes.
    TCSADRAIN: flush output, then change attributes.
    TCSAFLUSH: flush output and discard input, then change attributes.
  */

  BOOL dropDTR = FALSE;
  COMMTIMEOUTS to;
  DCB state;

  if ((action == TCSADRAIN) || (action == TCSAFLUSH))
    FlushFileBuffers (get_handle ());
  if (action == TCSAFLUSH)
    PurgeComm (get_handle (), (PURGE_RXABORT | PURGE_RXCLEAR));

  /* get default/last comm state */
  if (GetCommState (get_handle (), &state) == 0)
    return -1;

  /* -------------- Set baud rate ------------------ */
  /* FIXME: WIN32 also has 14400, 56000, 128000, and 256000.
     Unix also has 230400. */

  switch (t->c_ospeed)
    {
      case B0:	/* drop DTR */
        dropDTR = TRUE;
        state.BaudRate = 0;
        break;
      case B110:
        state.BaudRate = CBR_110;
        break;
      case B300:
        state.BaudRate = CBR_300;
        break;
      case B600:
        state.BaudRate = CBR_600;
        break;
      case B1200:
        state.BaudRate = CBR_1200;
        break;
      case B2400:
        state.BaudRate = CBR_2400;
        break;
      case B4800:
        state.BaudRate = CBR_4800;
        break;
      case B9600:
        state.BaudRate = CBR_9600;
        break;
      case B19200:
        state.BaudRate = CBR_19200;
        break;
      case B38400:
        state.BaudRate = CBR_38400;
        break;
      case B57600:
        state.BaudRate = CBR_57600;
        break;
      case B115200:
        state.BaudRate = CBR_115200;
        break;
      default:
        /* Unsupported baud rate! */
        termios_printf ("Invalid t->c_ospeed of %d\n", t->c_ospeed);
        set_errno (EINVAL);
        return -1;
    }

  /* -------------- Set byte size ------------------ */

  switch (t->c_cflag & CSIZE)
    {
      case CS5:
        state.ByteSize = 5;
        break;
      case CS6:
        state.ByteSize = 6;
        break;
      case CS7:
        state.ByteSize = 7;
        break;
      case CS8:
        state.ByteSize = 8;
        break;
      default:
        /* Unsupported byte size! */
        termios_printf ("Invalid t->c_cflag byte size of %d\n",
                                                  t->c_cflag & CSIZE);
        set_errno (EINVAL);
        return -1;
    }

  /* -------------- Set stop bits ------------------ */
 
  if (t->c_cflag & CSTOPB)
    state.StopBits = TWOSTOPBITS;
  else
    state.StopBits = ONESTOPBIT;

  /* -------------- Set parity ------------------ */

  if (t->c_cflag & PARENB)
    state.Parity = (t->c_cflag & PARODD) ? ODDPARITY : EVENPARITY;
  else
    state.Parity = NOPARITY;

  state.fBinary = TRUE;     /* Binary transfer */
  state.EofChar = 0;        /* No end-of-data in binary mode */
  state.fNull = FALSE;      /* Don't discard nulls in binary mode */

  /* -------------- Parity errors ------------------ */
  /* fParity combines the function of INPCK and NOT IGNPAR */

  if ((t->c_iflag & INPCK) && (! t->c_iflag & IGNPAR))
    state.fParity = TRUE;   /* detect parity errors */
  else
    state.fParity = FALSE;  /* ignore parity errors */

  /* Only present in Win32, Unix has no equivalent */
  state.fErrorChar = FALSE;
  state.ErrorChar = 0;

  /* -------------- Set software flow control ------------------ */
  /* Set fTXContinueOnXoff to FALSE.  This prevents the triggering of a
     premature XON when the remote device interprets a received character
     as XON (same as IXANY on the remote side).  Otherwise, a TRUE
     value separates the TX and RX functions. */

  state.fTXContinueOnXoff = TRUE;     /* separate TX and RX flow control */

  /* Transmission flow control */
  if (t->c_iflag & IXON)
    state.fOutX = TRUE;   /* enable */
  else
    state.fOutX = FALSE;  /* disable */

  /* Reception flow control */
  if (t->c_iflag & IXOFF)
    state.fInX = TRUE;    /* enable */
  else
    state.fInX = FALSE;   /* disable */

  /* XoffLim and XonLim are left at default values */

  state.XonChar = (t->c_cc[VSTART] ? t->c_cc[VSTART] : 0x11);
  state.XoffChar = (t->c_cc[VSTOP] ? t->c_cc[VSTOP] : 0x13);

  /* -------------- Set hardware flow control ------------------ */

  /* Disable DSR flow control */
  state.fOutxDsrFlow = FALSE;

  /* Some old flavors of Unix automatically enabled hardware flow
     control when software flow control was not enabled.  Since newer
     Unices tend to require explicit setting of hardware flow-control,
     this is what we do. */

  /* Input flow control */
  /* CLOCAL causes all lead control (except DTR) to be ignored */
  if ((t->c_cflag & CRTSXOFF) && (! (t->c_cflag & CLOCAL)))
    state.fRtsControl = RTS_CONTROL_HANDSHAKE;      /* enable */
  else
    state.fRtsControl = RTS_CONTROL_DISABLE;        /* disable */

  /* Output flow control */
  if ((t->c_cflag & CRTSCTS) && (! (t->c_cflag & CLOCAL)))
    state.fOutxCtsFlow = TRUE;    /* enable */
  else
    state.fOutxCtsFlow = FALSE;   /* disable */

  /* -------------- DTR ------------------ */
  /* Assert DTR on device open */

  state.fDtrControl = DTR_CONTROL_ENABLE;

  /* -------------- DSR ------------------ */
  /* Assert DSR at the device? */

  if (t->c_cflag & CLOCAL)
    state.fDsrSensitivity = FALSE;  /* no */
  else
    state.fDsrSensitivity = TRUE;   /* yes */

  /* -------------- Error handling ------------------ */
  /* Since read/write operations terminate upon error, we
     will use ClearCommError() to resume. */

  state.fAbortOnError = TRUE;

  /* -------------- Set state and exit ------------------ */
  SetCommState (get_handle (), &state);

  set_r_binary ((t->c_iflag & IGNCR) ? 0 : 1);
  set_w_binary ((t->c_oflag & ONLCR) ? 0 : 1);

  vtime_ = t->c_cc[VTIME];
  vmin_ = t->c_cc[VMIN];

  if (dropDTR == TRUE)
    EscapeCommFunction (get_handle (), CLRDTR);
  else
    {
      /* FIXME: Sometimes when CLRDTR is set, setting
      state.fDtrControl = DTR_CONTROL_ENABLE will fail.  This
      is a problem since a program might want to change some
      parameters while DTR is still down. */

      EscapeCommFunction (get_handle (), SETDTR);
    }

  memset (&to, 0, sizeof (to));

  to.ReadTotalTimeoutConstant = vtime_ * 100;

  int res = SetCommTimeouts (get_handle (), &to);
  if (!res)
    {
      small_printf ("CommTimeout failed\n");
      __seterrno ();
      return -1;
    }

  return 0;
}

/* tcgetattr: POSIX 7.2.1.1 */
int
fhandler_tty::tcgetattr (struct termios *t)
{
  DCB state;

  /* Get current Win32 comm state */
  if (GetCommState (get_handle (), &state) == 0)
    return -1;

  /* for safety */
  memset (t, 0, sizeof (*t));

  /* -------------- Baud rate ------------------ */

  switch (state.BaudRate)
    {
      case 0:
        /* FIXME: need to drop DTR */
        t->c_cflag = t->c_ospeed = t->c_ispeed = B0;
        break;
      case CBR_110:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B110;
        break;
      case CBR_300:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B300;
        break;
      case CBR_600:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B600;
        break;
      case CBR_1200:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B1200;
        break;
      case CBR_2400:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B2400;
        break;
      case CBR_4800:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B4800;
        break;
      case CBR_9600:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B9600;
        break;
      case CBR_19200:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B19200;
        break;
      case CBR_38400:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B38400;
        break;
      case CBR_57600:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B57600;
        break;
      case CBR_115200:
        t->c_cflag = t->c_ospeed = t->c_ispeed = B115200;
        break;
      default:
        /* Unsupported baud rate! */
        termios_printf ("Invalid baud rate of %d\n", state.BaudRate);
        set_errno (EINVAL);
        return -1;
    }

  /* -------------- Byte size ------------------ */

  switch (state.ByteSize)
    {
      case 5:
        t->c_cflag |= CS5;
        break;
      case 6:
        t->c_cflag |= CS6;
        break;
      case 7:
        t->c_cflag |= CS7;
        break;
      case 8:
        t->c_cflag |= CS8;
        break;
      default:
        /* Unsupported byte size! */
        termios_printf ("Invalid byte size of %d\n", state.ByteSize);
        set_errno (EINVAL);
        return -1;
    }

  /* -------------- Stop bits ------------------ */

  if (state.StopBits == TWOSTOPBITS)
    t->c_cflag |= CSTOPB;

  /* -------------- Parity ------------------ */

  if (state.Parity == ODDPARITY)
    t->c_cflag |= (PARENB | PARODD);
  if (state.Parity == EVENPARITY)
    t->c_cflag |= PARENB;

  /* -------------- Parity errors ------------------ */

  /* fParity combines the function of INPCK and NOT IGNPAR */
  if (state.fParity == TRUE)
    t->c_iflag |= INPCK;
  else
    t->c_iflag |= IGNPAR;	/* not necessarily! */

  /* -------------- Software flow control ------------------ */

  /* transmission flow control */
  if (state.fOutX == TRUE)
    t->c_iflag |= IXON;

  /* reception flow control */
  if (state.fInX == TRUE)
    t->c_iflag |= IXOFF;

  t->c_cc[VSTART] = (state.XonChar ? state.XonChar : 0x11);
  t->c_cc[VSTOP] = (state.XoffChar ? state.XoffChar : 0x13);

  /* -------------- Hardware flow control ------------------ */
  /* Some old flavors of Unix automatically enabled hardware flow
     control when software flow control was not enabled.  Since newer
     Unices tend to require explicit setting of hardware flow-control,
     this is what we do. */

  /* Input flow-control */
  if (state.fRtsControl == RTS_CONTROL_HANDSHAKE)
    t->c_cflag |= CRTSXOFF;

  /* Output flow-control */
  if (state.fOutxCtsFlow == TRUE)
    t->c_cflag |= CRTSCTS;

  /* -------------- CLOCAL --------------- */
  /* DSR is only lead toggled only by CLOCAL.  Check it to see if
     CLOCAL was called. */
  /* FIXME: If tcsetattr() hasn't been called previously, this may
     give a false CLOCAL. */

  if (state.fDsrSensitivity == FALSE)
    t->c_cflag |= CLOCAL;

  /* FIXME: need to handle IGNCR */
#if 0
  if (!get_r_binary ())
    t->c_iflag |= IGNCR;
#endif

  if (!get_w_binary ())
    t->c_oflag |= ONLCR;

  t->c_cc[VTIME] = vtime_;
  t->c_cc[VMIN] = vmin_;

  return 0;
}

/**********************************************************************/
/* /dev/null */

fhandler_dev_null::fhandler_dev_null (const char *name) : fhandler_base (name)
{;}

fhandler_base *
fhandler_dev_null::open (const char *, int flags, mode_t mode)
{
  return fhandler_base::open ("nul", flags, mode);
}

void
fhandler_dev_null::dump (void)
{
  paranoid_printf ("FHANDLER DEV/NULL\n");
}

/**********************************************************************/
/* fhandler_pipe */

fhandler_pipe::fhandler_pipe (const char *name) : fhandler_base (name)
{
  debug_printf("fhandler_pipe %s\n", name);
}

off_t
fhandler_pipe::lseek (off_t offset, int whence)
{ 
  debug_printf ("(%d, %d)\n", offset, whence);
  set_errno (ESPIPE);
  return -1;
}

/**********************************************************************/
/* fhandler_dev_floppy */

fhandler_dev_floppy::fhandler_dev_floppy (const char *name) : fhandler_base (name)
{;}

fhandler_base *
fhandler_dev_floppy::open (const char *path, int flags, mode_t)
{
  /* Always open a floppy existings */
  return fhandler_base::open (path, flags & ~(O_CREAT|O_TRUNC));
}

/**********************************************************************/
/* fhandler_dev_tape */

fhandler_dev_tape::fhandler_dev_tape(const char *name) : fhandler_base (name)
{;}

fhandler_base *
fhandler_dev_tape::open (const char *path, int flags, mode_t)
{
  /* Always open a tape existings */
  return fhandler_base::open (path, flags & ~(O_CREAT|O_TRUNC));
}

