// Build don't link: 
// GROUPS passed divergence
// excess errors test - XFAIL *-*-*
// divergence file
// From: baud@bone.research.att.com (Kurt Baudendistel)
// Date:     Tue, 5 Oct 93 16:37:40 -0400
// Subject:  Forward declaration in the parameter list
// Message-ID: <9310052037.AA21411@bone>

        int func (int i; int a[i], int i) { return 1; }
