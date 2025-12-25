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
		width: 70%;
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
	
	.menu_search{
		width: 30%;
		height: inherit;
		white-space: nowrap;
		overflow: hidden;
		font-family: 微軟正黑體,新細明體,標楷體;
		font-weight: bold;
		font-size: 17px;
		color: white;
	}
	.menu_search tr {
		display: block;
	}
	.menu_search td {
		height: 40px;
		padding: 0px 15px 0px 15px;
	}
	.menu_search td:hover {
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
	function ChangeContent(ToyID){
		document.getElementById("ToyID").value = ToyID;
		document.getElementById("mfrom").action = "toy_edit.php";
		document.getElementById("mfrom").submit();
	}
	
	function UpdateContent(){
		document.getElementById("ToyID").value = document.getElementById("ToyID").value;
		document.getElementById("TName").value = document.getElementById("TName").value;
		document.getElementById("Price").value = document.getElementById("Price").value;
		document.getElementById("Description").value = document.getElementById("Description").value;
		document.getElementById("Name").value = document.getElementById("Name").value;
		document.getElementById("Address").value = document.getElementById("Address").value;
		document.getElementById("Phone").value = document.getElementById("Phone").value;
		document.getElementById("mfrom").action = "toy_mdysave.php";
		document.getElementById("mfrom").submit();
	}
	
	function DeleteContent(){
		document.getElementById("ToyID").value = document.getElementById("ToyID").value;
		document.getElementById("mfrom").action = "toy_delsave.php";
		document.getElementById("mfrom").submit();
	}
	
	function InsertContent(){
		document.getElementById("mfrom").action = "toy_add.php";
		document.getElementById("mfrom").submit();
	}
  </script>
</head>
<body>
<form id="mfrom" method="post" action="toy_edit.php">
	<input type="hidden" id="ToyID" name="ToyID" value="<?php echo isset($_POST["ToyID"])?$_POST["ToyID"]:""?>">
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
		<table class="menu_search">
			<tr>
				<td>
					<form method="post" action="toy.php">
					Search
					  <input type="text" id="keyword" name="keyword" value="" placeholder="輸入搜尋關鍵字" />
					  <input type="submit" value="送出">				
					</form>
				</td>
			</tr>
		</table>
	</div>
	<div class="content">
		<div class="inner_content">
			<table class="table">
			  <input class="btn btn-default" type="button" value="新增" onclick="InsertContent();">
			  <div style="text-align: left;font-family: &quot;Helvetica Neue&quot;,Helvetica,Arial,sans-serif;font-size: 15px;font-weight: bold;">
				總數量為: 
			<?php
				$sql = "SELECT COUNT(*) FROM toy WHERE AreaCode = '201609260001'";
				$stmt =  $db->prepare($sql);
				$error = $stmt->execute();
				
				if($rowcount = $stmt->fetchColumn())
					echo $rowcount;
			?>
			  </div>
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
				<?php
					if(isset($_POST["ToyID"]) && !empty($_POST["ToyID"])){
						$ToyID = $_POST["ToyID"];
						
						$sql = "SELECT t.ToyID,t.Name TName,t.Price,t.Description,ts.Name,ts.Address,ts.Phone FROM `toy` t left join `toysupplier` ts on t.ToyID = ts.ToyID WHERE t.ToyID = ?";
						if($stmt = $db->prepare($sql)){
						$stmt->execute(array($ToyID));			
						if($result = $stmt->fetch()){						
				?>
						<tr> 
						  <th scope="row">
						  	<a class="btn btn-default" role="button" onclick="UpdateContent();">按我更新</a>
						  	<a class="btn btn-default" role="button" onclick="DeleteContent();">按我刪除</a>
						  </th> 
						  <td><input type="text" id="TName" name="TName" value="<?php echo $result['TName'];?>"/></td> 
						  <td><input type="text" id="Price" name="Price" value="<?php echo $result['Price'];?>"/></td> 
						  <td><input type="text" id="Description" name="Description" value="<?php echo $result['Description'];?>"/></td> 
						  <td><input type="text" id="Name" name="Name" value="<?php echo $result['Name'];?>"/></td> 
						  <td><input type="text" id="Address" name="Address" value="<?php echo $result['Address'];?>"/></td> 
						  <td><input type="text" id="Phone" name="Phone" value="<?php echo $result['Phone'];?>"/></td> 
						</tr> 
				<?php
						}
						}
					}else if (isset($_POST["keyword"]) && !empty($_POST["keyword"])){
						$keyword = $_POST["keyword"];
						
						if($keyword == ''){
						  $keyword = '%';
						}else{
						  $keyword = '%'.$keyword.'%';
						}
						
						$sql = "SELECT t.ToyID,t.Name TName,t.Price,t.Description,ts.Name,ts.Address,ts.Phone FROM `toy` t left join `toysupplier` ts on t.ToyID = ts.ToyID where t.Name like ? or t.Price like ? or t.Description like ? or ts.Name like ? or ts.Address like ? or ts.Phone like ?";
						if($stmt = $db->prepare($sql)){
						$stmt->execute(array($keyword, $keyword, $keyword, $keyword, $keyword, $keyword));
						
						for($rows = $stmt->fetchAll(),$count = 0;$count<count($rows);$count++){
				?>
							<tr> 
							  <th scope="row"><?php echo $count;?></th> 
							  <td>
								<a onclick="ChangeContent('<?php echo $rows[$count]['ToyID'];?>');"><?php echo $rows[$count]['TName'];?></a>
							  </td> 
							  <td><?php echo $rows[$count]['Price'];?></td> 
							  <td><?php echo $rows[$count]['Description'];?></td> 
						      <td><?php echo $rows[$count]['Name'];?></td> 
						      <td><?php echo $rows[$count]['Address'];?></td> 
						      <td><?php echo $rows[$count]['Phone'];?></td> 
						    </tr> 
				<?php
						}			
						}
					}else{
						$sql = "SELECT t.ToyID,t.Name TName,t.Price,t.Description,ts.Name,ts.Address,ts.Phone FROM `toy` t left join `toysupplier` ts on t.ToyID = ts.ToyID";
					if($stmt = $db->prepare($sql)){
						$stmt->execute();
						
						
						for($rows = $stmt->fetchAll(), $count = 0; $count < count($rows); $count++){
				?>
						<tr> 
						  <th scope="row"><?php echo $count;?></th> 
						  <td>
							<a onclick="ChangeContent('<?php echo $rows[$count]['ToyID'];?>');"><?php echo $rows[$count]['TName'];?></a>
						  </td> 
						  <td><?php echo $rows[$count]['Price'];?></td> 
						  <td><?php echo $rows[$count]['Description'];?></td> 
						  <td><?php echo $rows[$count]['Name'];?></td> 
						  <td><?php echo $rows[$count]['Address'];?></td> 
						  <td><?php echo $rows[$count]['Phone'];?></td> 
						</tr> 
				<?php
						}
						}
					}
				?>
			  </tbody> 
			</table>
		</div>
	</div>
</form>
</body>
</html>