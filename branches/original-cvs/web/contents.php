<div id="contents">
<ul>
<?php 
$contents = array(
	'about.php' => 'About',
	'index.php' => 'News',
	'shots.php' => 'Screen Shots',
	'install.php' => 'Install',
	'http://sourceforge.net/projects/gtkadi' => 'Summary',
	'http://cvs.sourceforge.net/viewcvs.py/gtkadi/' => 'ViewCVS'
);
function get_page_link($page, $name)
{
	if ($page == basename($_SERVER['PHP_SELF']))
		return "<li><b>$name</b></li>";
	else
		return "<li><a href=$page>$name</a></li>";
}
foreach ($contents as $key=>$value)
{
	echo get_page_link($key, $value);
}
?>
</ul>
</div>
