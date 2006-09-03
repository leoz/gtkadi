<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
          "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html lang="en">
<?php include("head.php"); ?>
<body>
<?php include("header.php"); ?>
<div id="container">
<div id="content">
<?php include("left_bar.php"); ?>
<div id="main">

<h2>About</h2>

GTK ADI Library is a library containing GTK ADI widget.
ADI stands from Advanced Document Interface.
ADI is just another MDI (Multiple Document Interface) implementation.
It contains a common MDI interface widget and several MDI representations - views.
There are currently two views available: "classical for GTK"
tabbed MDI view and aligned MDI view.
The aligned MDI view gives a possibility to have all child windows visible
on the same parent screen but without wasted space between them as it usually
can happen when traditional MDI widget is used. Further development will
include also window MDI view, the view where all the child windows are
represented by the standard GTK windows or dialogs.

<h2>History</h2>

This widget was originally developed for some unpublished software in 2003 - 2005.
Since the software using this widget has a tendency to be never completed
I have decided to publish this widget as a separate LGPL library hoping that it can be useful for someone else.

<p/>

Oleg Romashin joined the project as a new developer and package creator in the fall of 2005.

<h2>Usage</h2>

This widget can be useful in the applications that need
to deal with several views of the same type,
for example, text editors, file managers and so on.

<h2>Caveats</h2>

Moving of the child window is not yet supported.

Mixed mode of the aligned view when some of the child windows
could be fixed and some could be sizeable is not yet supported.

</div>	
</div>
</div>
<div class="clearing"> </div>
<div id="footer">
	&copy; 2005 Leonid Zolotarev. All rights reserved.
	<br/>
	$Id$
</div>
</body>
</html>
