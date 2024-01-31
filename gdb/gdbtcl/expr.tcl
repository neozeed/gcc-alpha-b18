##
# Local procedure:
#
#	create_expr_window - Create expression display window
#
# Description:
#
#	Create the expression display window.
#

# Set delete_expr_num, and set -state of Delete button.
proc expr_update_button {num} {
  global delete_expr_num
  set delete_expr_num $num
  if {$num > 0} then {
    set state normal
  } else {
    set state disabled
  }
  .expr.buts.delete configure -state $state
}

proc add_expr {expr} {
  global expr_update_list
  global expr_num

  incr expr_num

  set e .expr.exprs
  set f e$expr_num

  checkbutton $e.updates.$f -text "" -relief flat \
    -variable expr_update_list($expr_num)
  text $e.expressions.$f -width 20 -height 1
  $e.expressions.$f insert 0.0 $expr
  bind $e.expressions.$f <1> "update_expr $expr_num"
  text $e.values.$f -width 20 -height 1

  # Set up some bindings.
  foreach frame {updates expressions values} {
    bind $e.$frame.$f <FocusIn> "expr_update_button $expr_num"
    bind $e.$frame.$f <FocusOut> "expr_update_button 0"
  }

  update_expr $expr_num

  pack $e.updates.$f -side top
  pack $e.expressions.$f -side top -expand yes -fill x
  pack $e.values.$f -side top -expand yes -fill x
}

proc delete_expr {} {
  global delete_expr_num
  global expr_update_list

  if {$delete_expr_num > 0} then {
    set e .expr.exprs
    set f e${delete_expr_num}

    destroy $e.updates.$f $e.expressions.$f $e.values.$f
    unset expr_update_list($delete_expr_num)
  }
}

proc update_expr {expr_num} {
  global expr_update_list

  set e .expr.exprs
  set f e${expr_num}

  set expr [$e.expressions.$f get 0.0 end]
  $e.values.$f delete 0.0 end
  if {! [catch {gdb_eval $expr} val]} {
    $e.values.$f insert 0.0 $val
  } {
    # FIXME consider flashing widget here.
  }
}

proc update_exprs {} {
	global expr_update_list

	foreach expr_num [array names expr_update_list] {
		if {$expr_update_list($expr_num)} {
			update_expr $expr_num
		}
	}
}

proc create_expr_window {} {
	global expr_num
	global delete_expr_num
	global expr_update_list

	if {[winfo exists .expr]} {raise .expr ; return}

	# All the state about individual expressions is stored in the
	# expression window widgets, so when it is deleted, the
	# previous values of the expression global variables become
	# invalid.  Reset to a known initial state.
	set expr_num 0
	set delete_expr_num 0
	catch {unset expr_update_list}
	set expr_update_list(0) 0

	toplevel .expr
	wm title .expr "GDB Expressions"
	wm iconname .expr "Expressions"

	frame .expr.entryframe -borderwidth 2 -relief raised
	label .expr.entryframe.entrylab -text "Expression: "
	entry .expr.entryframe.entry -borderwidth 2 -relief sunken
	bind .expr.entryframe.entry <Return> {
	  add_expr [.expr.entryframe.entry get]
	  .expr.entryframe.entry delete 0 end
	}

	pack .expr.entryframe.entrylab -side left
	pack .expr.entryframe.entry -side left -fill x -expand yes

	frame .expr.buts -borderwidth 2 -relief raised

	button .expr.buts.delete -text Delete -command delete_expr \
	  -state disabled

	button .expr.buts.close -text Close -command {destroy .expr}
	button .expr.buts.help -text Help -state disabled

	pack .expr.buts.delete -side left
	pack .expr.buts.help .expr.buts.close -side right

	pack .expr.buts -side bottom -fill x
	pack .expr.entryframe -side bottom -fill x

	frame .expr.exprs -borderwidth 2 -relief raised

	# Use three subframes so columns will line up.  Easier than
	# dealing with BLT for a table geometry manager.  Someday Tk
	# will have one, use it then.  FIXME this messes up keyboard
	# traversal.
	frame .expr.exprs.updates -borderwidth 0 -relief flat
	frame .expr.exprs.expressions -borderwidth 0 -relief flat
	frame .expr.exprs.values -borderwidth 0 -relief flat

	label .expr.exprs.updates.label -text Update
	pack .expr.exprs.updates.label -side top -anchor w
	label .expr.exprs.expressions.label -text Expression
	pack .expr.exprs.expressions.label -side top -anchor w
	label .expr.exprs.values.label -text Value
	pack .expr.exprs.values.label -side top -anchor w

	pack .expr.exprs.updates -side left
	pack .expr.exprs.values .expr.exprs.expressions \
	  -side right -expand 1 -fill x

	pack .expr.exprs -side top -fill both -expand 1 -anchor w
}

#
# Local procedure:
#
#	display_expression (expression) - Display EXPRESSION in display window
#
# Description:
#
#	Display EXPRESSION and its value in the expression display window.
#

proc display_expression {expression} {
	create_expr_window

	add_expr $expression
}
