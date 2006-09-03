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

<h2>Install</h2>

<h3>Build process</h3>

For to build and install the GtkAdi library you need to do these steps:

<ol>
	<li>Download latest source package</li>
	<li>Unpack it</li>
	<li>Configure
    <pre>$ ./autogen.sh<br>$ ./configure -prefix=/usr --enable-widgets=yes</pre>
	Notes
		<ul>
		<li>
		<span style="font-weight: bold;">-prefix=/usr</span> - Debian specific option.
		</li>
		<li>
		<span style="font-weight: bold;">--enable-widgets=yes</span> - Enables toolbar and menu bar (disabled by default).
		<br/>
		You need this option to compile test program. 
		</li>
		</ul>
		<br/>
    </li>
	<li>Compile
    <pre>$ make</pre>
	</li>
	<li>Install
    <pre>$ sudo make install</pre>
	</li>
</ol>

<h3>Build process automation</h3>

There is a way to speedup the build process a little.

<ol>
	<li>A script build_source.sh in $HOME/bin directory:
    <pre>#!/bin/sh<br>./autogen.sh<br>./configure -prefix=/usr --enable-widgets=yes<br>make<br>sudo make install</pre>
	</li>
	<li>Alias in $HOME/.bashrc
    <pre>alias bs='~/bin/build_source.sh'</pre>
	</li>
	<li>Type 'bs' in the source directory and press enter.
	</li>
</ol>

</div>	
</div>
</div>
<div class="clearing"> </div>
<div id="footer">
	&copy; 2006 Leonid Zolotarev. All rights reserved.
	<br/>
	$Id$
</div>
</body>
</html>
