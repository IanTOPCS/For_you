<?php
	include("../function/condb.php");
	
	if (isset($_POST["ToyID"]) && !empty($_POST["ToyID"]))
	{
	  $ToyID = $_POST["ToyID"];
	  
	  $sql = "DELETE FROM toy WHERE ToyID = ?";
	  if($stmt = $db->prepare($sql)){
		$success = $stmt->execute(array($ToyID));
		  
		  if (!$success) {
			echo "刪除失敗!".$stmt->errorInfo();
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