-- 1.	Find the ID, name, and manager of each employee who works for “FirstBank”.
select e.id as ID, e.person_name as name, m.person_name as manager from employee as e
inner join works as w on w.id = e.id
left join manages as mid on mid.id = e.id
left join employee as m on m.id = mid.manager_id
where w.company_name = 'FirstBank';

-- 2.	Find the ID of each employee who does not work for “FirstBank”.
select e.id as ID from employee as e
inner join works as w on w.id = e.id
where w.company_name <> 'FirstBank';

select w.id as ID from works as w
where w.company_name <> 'FirstBank';

-- 3.	Find the ID and name of each employee who lives in the same city as the location of the company for which the employee works.
select e.id as ID, e.person_name as name from employee as e
inner join company as c on c.city = e.city
inner join works as w on w.id = e.id
where w.company_name = c.company_name;

-- 4.	Find the ID of each employee who earns more than at least one employee of “SmallBank”.
-- a. (1)	Please use “tuple variable”.
select distinct w_other.id as ID from works as w_other, works as w_smb
where w_other.salary>w_smb.salary and w_smb.company_name='SmallBank';
-- 特別：自己公司SmallBank內互比，賺的比其中一人多也算(ID = 10003)

-- b. (2)	Please use “nested subquery” in the WHERE clause.
select w.id as ID from works as w
where w.salary > (
    select distinct min(sb.salary) from works as sb
    where sb.company_name='SmallBank'
);
-- 解二
select w.id as ID from works as w
where w.salary > some(
    select sb.salary from works as sb
    where sb.company_name='SmallBank'
);
-- 特別：subquery 可能回傳多個值(100000 >70856且>45493)，故取min

-- 5.	Find the name of each company whose employees earn a higher salary, on average, than the average salary at “FirstBank”.
-- (1) Please use “having”
select w.company_name as company from works as w
group by w.company_name
having avg(w.salary) > (
    select avg(fb.salary) from works as fb
    where fb.company_name = 'FirstBank'
);
-- (2) Please use “with”.
with cte as (
    select w.company_name as company_name, avg(w.salary) as savg from works as w
    where w.company_name <> 'FirstBank'
    group by w.company_name
), cte2 as (
    select avg(w.salary) as savg from works as w
    where w.company_name = 'FirstBank'
    group by w.company_name
)
select c.company_name as company_name from cte as c
cross join cte2 as c2
where c.savg > c2.savg;
-- 解二
with cte as (
    select avg(fb.salary) as avgfb from works as fb
    where fb.company_name = 'FirstBank'
)
select w.company_name as company from works as w
group by w.company_name
having avg(w.salary) > (
    select avgfb from cte
);
-- 解三
with cte as (
    select fb.salary as avgfb from works as fb
    where fb.company_name = 'FirstBank'
)
select w.company_name as company from works as w, cte
group by w.company_name
having avg(w.salary) > avg(cte.avgfb);

-- 6.	Delete all tuples in the works relation for employees of “SmallBank”.
delete from works as w
where w.company_name = 'SmallBank';

-- 7.	Add a new employee with the ID as “E01” and the name as “John”, but the address is currently unknown.
insert into employee values ('E01', 'John', null, null);

-- 8.	Give each employee of “FirstBank” a 10-percent raise of salaries unless the salary becomes greater than $100000; in such cases, give only a 3-percent raise.
update works as w
set w.salary = 
    case
        when w.salary * 1.10 <= 100000 then w.salary*1.1
        else w.salary*1.03
    end
where w.company_name = 'FirstBank';

select distinct w.company_name as name from works as w
where avg_salary(w.company_name) > avg_salary('FirstBank');

select w.company_name as name, avg_salary(w.company_name) as avgSalary from works as w
group by w.company_name;