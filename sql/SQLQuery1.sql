-- https://www.sqlservertutorial.net/sql-server-basics/

use SCL2

SELECT
	name
FROM
	master.sys.databases
ORDER BY
	name

EXEC sp_databases

--CREATE DATABASE SCL2

-- DROP DATABASE SCL2

--CREATE SCHEMA scl_test