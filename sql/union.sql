/**
* 查找两个表中不同时拥有的employee_id。
* MySQL无法直接作差，但可以并：union。
* select from () as alias 括号里的表必须有名字，如是派生表则必须命名。
*/
SELECT employee_id
From Employees
WHERE employee_id not in (
    SELECT employee_id From Salaries
)
UNION
SELECT employee_id
From Salaries
WHERE employee_id not in (
    SELECT employee_id From Employees
)
ORDER BY employee_id