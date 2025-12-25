<?php
	include("../function/condb.php");
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
	
	.menu a {
		text-decoration: none;
		color: white;
		font-family: 微軟正黑體,新細明體,標楷體;
		font-weight: bold;
		font-size: 17px;
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
		background-color: #f1f1f1;
	}
	
	.inner_content {
		padding: 50px 130px 220px 130px;
	}
	
	.inner_content table {
		background-color: white;
	}
	
	li img {
		width: 100%;
		height: 100%;
	}
	
	input[type=text] {
		color: black;
	}
	
	form {
		margin-bottom: 0em;
	}
  </style>
  <link type="text/css" rel="stylesheet" href="bootstrap-3.3.7-dist/css/bootstrap.css">
  <link type="text/css" rel="stylesheet" href="bootstrap-3.3.7-dist/css/bootstrap.min.css">
  <link type="text/css" rel="stylesheet" href="bootstrap-3.3.7-dist/css/bootstrap-theme.css">
  <link type="text/css" rel="stylesheet" href="bootstrap-3.3.7-dist/css/bootstrap-theme.min.css">
  <script>	
	function InsertContent(){
		document.getElementById("TName").value = document.getElementById("TName").value;
		document.getElementById("Price").value = document.getElementById("Price").value;
		document.getElementById("Description").value = document.getElementById("Description").value;
		document.getElementById("Name").value = document.getElementById("Name").value;
		document.getElementById("Address").value = document.getElementById("Address").value;
		document.getElementById("Phone").value = document.getElementById("Phone").value;
		document.getElementById("mfrom").action = "toy_addsave.php";
		document.getElementById("mfrom").submit();
	}
  </script>
</head>
<body>
<form id="mfrom" method="post" action="toy_edit.php">
	<div class="menu">
		<table class="menu_css">
			<tr>
				<td>
					<a href="../index.php">Home</a>
				</td>
				<td>
					<a href="toy.php">玩具屋</a>
				</td>
				<td>
					<a href="toy_edit.php">編輯玩具屋</a>
				</td>
			</tr>
		</table>
	</div>
	<div class="content">
		<div class="inner_content">
			<table class="table">
			  <thead>
				<tr> 
				  <th>#</th> 
				  <th>玩具</th> 
				  <th>玩具價錢</th> 
				  <th>玩具描述</th> 
				  <th>廠商名字</th> 
				  <th>廠商地址</th> 
				  <th>廠商電話</th> 
				</tr>  
			  </thead> 
			  <tbody>
					<tr> 
					  <th scope="row"><a onclick="InsertContent();">按我新增</a></th> 
					  <td><input type="text" id="TName" name="TName" value=""/></td> 
					  <td><input type="text" id="Price" name="Price" value=""/></td> 
					  <td><input type="text" id="Description" name="Description" value=""/></td> 
					  <td><input type="text" id="Name" name="Name" value=""/></td> 
					  <td><input type="text" id="Address" name="Address" value=""/></td> 
					  <td><input type="text" id="Phone" name="Phone" value=""/></td> 
					</tr> 
			  </tbody> 
			</table>
		</div>
	</div>
</form>
</body>
</html>