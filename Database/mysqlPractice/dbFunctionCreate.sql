DELIMITER $$

CREATE FUNCTION avg_salary(companyName VARCHAR(30)) RETURNS DECIMAL(10,2)
DETERMINISTIC
BEGIN
    DECLARE ans DECIMAL(10,2);
        SELECT AVG(salary) INTO ans FROM works
        WHERE company_name = companyName;
    RETURN ans;
END $$

DELIMITER ;
