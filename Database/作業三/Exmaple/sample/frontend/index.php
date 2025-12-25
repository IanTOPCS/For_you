<?php
	include("function/condb.php");
?>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  <title>index.php</title>
  <style>
	body {
		margin: 0px;
	}
	a {
		text-decoration: none;
		color: white;
		font-family: 微軟正黑體,新細明體,標楷體;
		font-weight: bold;
		font-size: 17px;
	}
	
	.menu {
		position:fixed;
		width: 100%;
		height: 40px;
		background-color: dimgrey;
		z-index: 9999999;
	}
	
	.menu_css {
		float: left;
		width: 100%;
		height: inherit;
		overflow: hidden;
		font-family: 微軟正黑體,新細明體,標楷體;
		font-weight: bold;
		font-size: 17px;
		color: white;
		border-spacing: 0px;
	}
	.menu_css tr {
		display: block;
	}
	.menu_css td {
		height: 40px;
		padding: 0px 15px 0px 15px;
		white-space: nowrap;
	}
	.menu_css td:hover {
		background-color: black;
	}
	
	.content {
		position: relative;
		word-wrap: break-word;
		width: 100%;
		top: 40px;
	}
	
	li img {
		width: 100%;
		height: 100%;
	}
  </style>
  <script src="js/jquery.min.js"></script>
  <script src="js/jquery.bxslider.min.js"></script>
  <link href="css/jquery.bxslider.min.css" rel="stylesheet" />
  <script>
	$(document).ready(function(){
	  slider = $('.bxslider').bxSlider(
		  {
			  pagerCustom: '#bx-pager'
		  }
	  );
	  slider.startAuto();
	});
  </script>
</head>
<body>
<div class="menu">
	<table class="menu_css">
		<tr>
			<td>
				<a href="index.php">Home</a>
			</td>
			<td>
				<a href="content/toy.php">玩具屋</a>
			</td>
			<td>
				<a href="content/toy_edit.php">編輯玩具屋</a>
			</td>
		</tr>
	</table>
</div>
<div class="content">
	<div>
		<ul class="bxslider">
		  <li><img src="image/1.jpg" /></li>
		  <li><img src="image/2.jpg" /></li>
		  <li><img src="image/3.jpg" /></li>
		  <li><img src="image/4.jpg" /></li>
		</ul>
	</div>
</div>
</body>
</html>