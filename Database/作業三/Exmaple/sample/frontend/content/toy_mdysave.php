<?php
	include("../function/condb.php");
	
	if (isset($_POST["ToyID"]))
	{
	  $ToyID = $_POST["ToyID"];
	  $TName = $_POST["TName"];
	  $Price= $_POST["Price"];
	  $Description = $_POST["Description"];
	  $Name = $_POST["Name"];
	  $Address = $_POST["Address"];
	  $Phone = $_POST["Phone"];
	  
	  if($TName == ''){
		 $TName = '更換玩具名稱';
	  }
	  
	  $sql = "UPDATE toy T LEFT JOIN toysupplier TS ON T.ToyID = TS.ToyID SET T.Name = ?,T.Price = ?,T.Description = ?,TS.Name = ?,TS.Address = ?,TS.Phone = ? WHERE T.ToyID = ?";
	  if($stmt = $db->prepare($sql)){
	  $success = $stmt->execute(array($TName, $Price, $Description, $Name, $Address, $Phone, $ToyID));
	  
	  if (!$success) {
	    echo "儲存失敗!".$stmt->errorInfo();
	    
	    $sql = "INSERT INTO toysupplier (ToyID,Name,Address,Phone) values (?,?,?,?) ";  
	    if($stmt = $db->prepare($sql)){
	    $success = $stmt->execute(array($ToyID, $Name, $Address, $Phone));
			  
		if (!$success) {
		    echo "儲存失敗!".$stmt->errorInfo();
		}else{
			header('Location: toy_edit.php');
		}
		}
	  }else{
	  	header('Location: toy_edit.php');
	  }
	  }
	} 
	else 
	{
	  $ToyID = NULL;
	  echo "no supplied";
	}	
	
	
?>