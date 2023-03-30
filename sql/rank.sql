/*
 *  每个部门前三高的工资
 *  https://leetcode.cn/problems/department-top-three-salaries/description/
 */

select t.Department, t.Employee, t.Salary
from
(
    select t2.name Department, t1.name Employee, t1.salary Salary,       
    dense_rank() over(partition by t1.departmentId order by t1.salary DESC) sarank   /* 分部门生成排名  */
    from Employee t1 join Department t2 
    where t1.departmentId = t2.id
    -- and sarank <= 3          /* 不能 */
) as t
where t.sarank <= 3;