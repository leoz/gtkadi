<div id="contents">
<ul>
<?php 
$contents = array(
	'index.php' => 'News',
	'http://sourceforge.net/projects/gtkadi' => 'Summary'
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
