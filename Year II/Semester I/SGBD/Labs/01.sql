-- 9
SELECT CONCAT(last_name, ' ' || first_name) "Nume"
FROM employees
WHERE SUBSTR(UPPER(first_name), 3, 1) = 'A';

-- 10
SELECT CONCAT(last_name, ' ' || first_name) "Nume"
FROM employees
WHERE (UPPER(first_name) LIKE '%L%L%' AND department_id = 30) OR manager_id = 102;

-- 11
SELECT CONCAT(last_name, ' ' || first_name) "Nume", job_id, salary
FROM employees
WHERE (UPPER(job_id) LIKE '%CLERK%' OR 
       UPPER(job_id) LIKE '%REP%') AND
       salary NOT IN (1000, 2000, 3000);
       
-- 12
-- Varianta 1
SELECT CONCAT(last_name, ' ' || first_name) "Nume", department_name
FROM employees e
LEFT JOIN departments d ON (e.department_id = d.department_id);

-- Varianta 2
SELECT CONCAT(last_name, ' ' || first_name) "Nume", department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id (+);

-- 13
-- Varianta 1
SELECT department_name, CONCAT(last_name, ' ' || first_name) "Nume"
FROM employees e
RIGHT JOIN departments d ON (e.department_id = d.department_id);

-- Varianta 2
SELECT department_name, CONCAT(last_name, ' ' || first_name) "Nume"
FROM employees e, departments d
WHERE e.department_id (+) = d.department_id;

-- 14
SELECT e.employee_id, CONCAT(e.last_name, ' ' || e.first_name) "Nume Angajat", 
       s.employee_id, CONCAT(s.last_name, ' ' || s.first_name) "Nume Sef"
FROM employees e
JOIN employees s ON (e.manager_id = s.employee_id);

-- 15
-- Varianta 1
SELECT e.employee_id, CONCAT(e.last_name, ' ' || e.first_name) "Nume Angajat", 
       s.employee_id, CONCAT(s.last_name, ' ' || s.first_name) "Nume Sef"
FROM employees e
LEFT JOIN employees s ON (e.manager_id = s.employee_id);

-- Varianta 2
SELECT e.employee_id, CONCAT(e.last_name, ' ' || e.first_name) "Nume Angajat", 
       s.employee_id, CONCAT(s.last_name, ' ' || s.first_name) "Nume Sef"
FROM employees e, employees s
WHERE e.manager_id = s.employee_id (+);

-- 16
-- Varianta 1
SELECT department_id
FROM departments
MINUS
SELECT department_id
FROM employees;

-- Varianta 2
SELECT department_id
FROM employees
RIGHT JOIN departments USING (department_id)
WHERE employee_id IS NULL;

-- 17
SELECT MAX(salary) "Maxim", MIN(salary) "Minim", SUM(salary) "Suma", ROUND(AVG(salary), 2) "Media"
FROM employees;

-- 18
SELECT job_title, MAX(salary) "Maxim", MIN(salary) "Minim", SUM(salary) "Suma", ROUND(AVG(salary), 2) "Media"
FROM employees e
JOIN jobs j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title;

-- 19
SELECT job_title, COUNT(employee_id)
FROM employees e
JOIN jobs j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title;

-- 20
SELECT department_name "Nume departament", city "Locatie", COUNT(employee_id) "Nr. Angajati", ROUND(AVG(salary), 2) "Salariul mediu"
FROM employees e
JOIN departments d ON(e.department_id = d.department_id)
JOIN locations l ON(d.location_id = l.location_id)
GROUP BY department_name, d.location_id, city;
