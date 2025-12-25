<?php
  include("../function/condb.php");
	
  $TName = $_POST["TName"];
  $Price= $_POST["Price"];
  $Description = $_POST["Description"];
  $Name = $_POST["Name"];
  $Address = $_POST["Address"];
  $Phone = $_POST["Phone"];
  
  if($TName == ''){
	 $TName = '更換玩具名稱';
  }
  
  $sql = "INSERT INTO toy (ToyID,AreaCode,Name,Price,Description) values (NULL,201609260001,?,?,?)";
  if($stmt = $db->prepare($sql)){
  $success = $stmt->execute(array($TName, $Price, $Description));
  
  if (!$success) {
    echo "儲存失敗!".$stmt->errorInfo();
  }else{
  	$ToyID = $db->lastInsertId();
  }
  
  $sql = "INSERT INTO toysupplier (ToyID,Name,Address,Phone) values (?,?,?,?) ";  
  if($stmt = $db->prepare($sql)){
  $success = $stmt->execute(array($ToyID, $Name, $Address, $Phone));
  
  if (!$success) {
    echo "儲存失敗!".$stmt->errorInfo();
  }else{
  	header('Location: toy_edit.php');
  }
  }
  }
	
?>