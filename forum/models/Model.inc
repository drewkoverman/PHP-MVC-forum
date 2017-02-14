<?php
//Create model class object that sets DB connection and id properties
class Model {
	//Declare private variables
	protected $id;

	//Call and Declare class constructor 
    public function __construct($fields = array()) {
        $id = safeParam($fields, 'id');
        if ($id && is_numeric($id)) {
            $this -> setId($id);
        }	
    }

    public function getId() {
        return $this -> id;
    }

    public function setId($id) {
        $this -> id = $id;
        return $this;
    }
	
	//Static function to connect to SQLLite DB
	protected static function getDb() {
        try {
            $db = new PDO('sqlite:qa.db3');
        } catch (PDOException $e) {
            die("Could not open database. " . $e -> getMessage());
        }
        return $db;
    }

    protected static function adHocQuery($q) {
        $db = self::getDb();
        $st = $db -> prepare($q);
        $st -> execute();
        return $st -> fetchAll(PDO::FETCH_ASSOC);
    }
}
?>