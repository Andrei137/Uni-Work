-- Lab 1

-- 2
DESC EMPLOYEES;

-- 3
SELECT *
FROM EMPLOYEES;

-- 4
SELECT employee_id, last_name, job_id, hire_date
FROM EMPLOYEES;

-- 5
SELECT job_id
FROM EMPLOYEES;

SELECT DISTINC job_id
FROM EMPLOYEES;

-- 6
SELECT last_name || ', ' || first_name || ', ' || job_id "Detalii Angajat"
FROM EMPLOYEES;

-- 7
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > 2850;

-- 8
SELECT last_name, department_name
FROM EMPLOYEES
WHERE employee_id = 104;

-- 9
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary NOT BETWEEN 14000 and 24000;

-- 9.1
SELECT last_name, first_name, salary
FROM EMPLOYEES
WHERE salary BETWEEN 3000 AND 7000;

-- 9.2
SELECT last_name, first_name, salary
FROM EMPLOYEES
WHERE salary >= 3000 AND salary <= 7000;

-- 10
SELECT last_name, job_id, hire_date
FROM EMPLOYEES
WHERE hire_date BETWEEN '20-FEB-1987' AND '01-MAY-1989';
ORDER BY hire_date;

-- 11
SELECT last_name, department_id
FROM EMPLOYEES
WHERE department_id IN (10, 30)
ORDER BY last_name;

-- 12
SELECT last_name "Angajat", salary "Salariu lunar"
FROM EMPLOYEES
WHERE salary > 1500 AND department_id IN (10, 30)
ORDER BY last_name;

-- 13
SELECT SYSDATE
FROM DUAL;

-- 14
SELECT last_name, hire_date
FROM EMPLOYEES
WHERE hire_date LIKE ('%87%');

SELECT last_name, hire_date
FROM EMPLOYEES
WHERE TO_CHAR(hire_date, 'YYYY') = 1987;

-- 15
SELECT last_name, job_id
FROM EMPLOYEES
WHERE manager_id IS NULL;

-- 16
SELECT last_name, salary, commission_pct
FROM EMPLOYEES
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC, commission_pct DESC;

-- 17
SELECT last_name, salary, commission_pct
FROM EMPLOYEES
ORDER BY salary DESC, commission_pct DESC;

-- 18
SELECT last_name
FROM EMPLOYEES
WHERE UPPER(last_name) LIKE ('__A%');

-- 19
SELECT last_name
FROM EMPLOYEES
WHERE UPPER(last_name) LIKE ('%L%L%') AND department_id = 30 OR manager_id = 102;

-- 20
SELECT last_name, job_id, salary
FROM EMPLOYEES
where UPPER(job_id) LIKE ('%CLERK%') OR UPPER(job_id) LIKE ('%REP%') AND salary NOT IN (1000, 2000, 3000);


-- Lab 2

-- 1
SELECT CONCAT(first_name, ' ') || last_name || CONCAT(' castiga ', salary) || CONCAT(' lunar dar doreste ', 3 * salary) "Salariu ideal"
FROM EMPLOYEES;

-- 2
SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM EMPLOYEES
WHERE SUBSTR(UPPER(last_name), 1, 1) IN ('J', 'M'); AND SUBSTR(UPPER(last_name), 3, 1) = 'A';
ORDER BY 3 DESC;

SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM EMPLOYEES
WHERE (UPPER(last_name) LIKE ('J%') OR UPPER(last_name) LIKE ('M%')) AND UPPER(last_name) LIKE ('__A%')
ORDER BY 3 DESC;

-- 3
SELECT employee_id, last_name, department_id
FROM EMPLOYEES
WHERE TRIM(BOTH FROM UPPER(first_name)) = 'STEVEN';

SELECT employee_id, last_name, department_id
FROM EMPLOYEES
WHERE LTRIM(RTRIM(UPPER(first_name))) = 'STEVEN';

-- 4
SELECT employee_id, last_name, LENGTH(last_name), INSTR(UPPER(last_name), 'A', 1)
FROM EMPLOYEES
WHERE UPPER(SUBSTR(last_name, -1, 1)) = 'E';

-- 5
SELECT *
FROM EMPLOYEES
WHERE MOD(ROUND(SYSDATE - hire_date), 7) = 0; 

-- 6
SELECT employee_id, last_name, salary, ROUND(salary + salary * 0.15, 2) "Salariu nou", ROUND((salary + salary * 0.15) / 100, 2) "Numar sute"
FROM EMPLOYEES
WHERE MOD(salary, 1000) != 0;

-- 7
SELECT last_name "Nume angajat", RPAD(TO_CHAR(hire_date), 20) "Data angajarii"
FROM EMPLOYEES
WHERE commission_pct IS NOT NULL;

-- 8
SELECT TO_CHAR(SYSDATE + 30, 'MON-DD-YYYY HH24:MI:SS') "Data"
FROM DUAL; 

-- 9
SELECT TO_DATE('31-12-2023', 'DD-MM-YYYY') - SYSDATE
FROM DUAL;

-- 10
-- a)
SELECT TO_CHAR(SYSDATE + 12 / 24, 'DD-MON-YYYY HH24:MI:SS') "Data"
FROM DUAL;

-- b)
SELECT TO_CHAR(SYSDATE + 1 / 12 / 24, 'DD-MON-YYYY HH24:MI:SS') "Data"
FROM DUAL;

-- 11
SELECT CONCAT(last_name, CONCAT(' ', first_name)), hire_date, NEXT_DAY(ADD_MONTHS(hire_date, 6), 'MONDAY') "Negociere"
FROM EMPLOYEES;

-- 12
SELECT last_name, ROUND(MONTHS_BETWEEN(SYSDATE, hire_date)) "Luni lucrate"
FROM EMPLOYEES
ORDER BY 2;

-- 13
SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision') "Comision"
FROM EMPLOYEES;

-- 14
SELECT last_name, salary, commission_pct
FROM EMPLOYEES
WHERE salary + salary * NVL(commission_pct, 0) > 10000;

-- 15
SELECT last_name, job_id, salary,
CASE job_id WHEN 'IT_PROG' THEN salary * 1.1
            WHEN 'ST_CLERK' THEN salary * 1.15
            WHEN 'SA_REP' THEN salary * 1.2
            ELSE salary
END "Salariu renegociat"
FROM EMPLOYEES;

-- 16
SELECT employee_id, department_name
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id);

-- 17
SELECT DISTINCT e.job_id, job_title
FROM EMPLOYEES e
JOIN JOBS j ON(e.job_id = j.job_id)
WHERE department_id = 30;

-- 18
SELECT last_name, department_name, location_id
FROM EMPLOYEES e, DEPARTMENTS d
WHERE e.department_id = d.department_id AND commission_pct IS NOT NULL;

-- 19
SELECT last_name, job_title, department_name
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
JOIN JOBS j ON(e.job_id = j.job_id)
JOIN LOCATIONS l ON(d.location_id = l.location_id)
WHERE UPPER(city) = 'OXFORD';

-- 20
SELECT ang.employee_id "Ang#", ang.last_name "Angajat", mg.employee_id "Manager", mg.last_name "Mgr#" 
FROM EMPLOYEES ang
JOIN EMPLOYEES mg ON (ang.manager_id = mg.employee_id);

-- 21
SELECT ang.employee_id "Ang#", ang.last_name "Angajat", mg.employee_id "Manager", mg.last_name "Mgr#" 
FROM EMPLOYEES ang
LEFT JOIN EMPLOYEES mg ON (ang.manager_id = mg.employee_id);

-- 22
SELECT ang.last_name "Nume angajat", ang.department_id "Departament", coleg.last_name "Nume coleg"
FROM EMPLOYEES ang
JOIN EMPLOYEES coleg ON (ang.department_id = coleg.department_id ABD ang.employee_id > col.employee_id)
ORDER BY ang.last_name;

-- 23
SELECT last_name, e.job_id, job_title, department_name, salary
FROM EMPLOYEES e
JOIN JOBS j ON (e.job_id = j.job_id)
LEFT JOIN DEPARTMENTS d ON (e.department_id = d.department_id);

-- 24
SELECT ang.last_name NumeAng, ang.hire_date DataAng, gates.last_name NumeGates, gates.hire_date DataGates
FROM EMPLOYEES ang
JOIN EMPLOYEES gates ON (ang.hire_date > gates.hire_date)
WHERE INITCAP(gates.last_name) = 'Gates';

SELECT last_name, hire_date
FROM EMPLOYEES
WHERE hire_date > (
                    SELECT hire_date
                    FROM EMPLOYEES
                    WHERE INITCAP(last_name) = 'Gates'
                  );

-- 25
SELECT e.last_name "Angajat", e.hire_date "Data_ang",
       m.last_name "Manager", m.hire_date "Data_mgr"
FROM EMPLOYEES e
JOIN EMPLOYEES m ON (e.manager_id = m.employee_id 
                     AND e.hire_date < m.hire_date);


-- Lab 3

-- 1
SELECT last_name, TO_CHAR(hire_date, 'MONTH YYYY')
FROM EMPLOYEES
WHERE department_id = (
                         SELECT department_id
                         FROM EMPLOYEES
                         WHERE INITCAP(last_name) = 'Gates'
                      ) 
      AND INITCAP(last_name) != 'Gates' 
      AND UPPER(last_name) LIKE ('%A%');

-- 2
SELECT e.employee_id, e.last_name, department_name, e.department_id
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON (e.department_id = d.department_id)
JOIN EMPLOYEES coleg ON (e.department_id = coleg.department_id)
WHERE UPPER(coleg.last_name) LIKE ('%T%')
      AND (e.employee_id != coleg.employee_id)
ORDER BY 2; 

-- 3
SELECT last_name, salary, job_title, city, country_name
FROM EMPLOYEES e
JOIN JOBS j ON (e.job_id = j.job_id)
JOIN DEPARTMENTS d ON (e.department_id = d.department_id)
JOIN LOCATIONS l ON (d.location_id = l.location_id)
JOIN COUNTRIES c ON (l.country_id = c.country_id)
WHERE e.manager_id IN (
                        SELECT employee_id
                        FROM EMPLOYEES 
                        WHERE INITCAP(last_name) = 'King'
                     );

-- 4
SELECT e.department_id, department_name, last_name, job_id, TO_CHAR(salary, '$99,999.00')
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
WHERE UPPER(department_name) LIKE ('%TI%')
ORDER BY 2, 3;

-- 5
SELECT last_name || ' ' || first_name "Nume prenume", department_name "Departament"
FROM EMPLOYEES
LEFT JOIN DEPARTMENTS USING (department_id)
UNION
SELECT last_name || ' ' || first_name, department_name
FROM EMPLOYEES
RIGHT JOIN DEPARTMENTS USING (department_id);

SELECT last_name || ' ' || first_name "Nume prenume", department_name "Departament"
FROM EMPLOYEES
FULL JOIN DEPARTMENTS USING (department_id);

-- 6
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) like '%RE%'
UNION
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'SA_REP';

-- 7
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) like '%RE%'
UNION ALL
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'SA_REP';

-- 8
SELECT department_id
FROM DEPARTMENTS
MINUS
SELECT department_id
FROM EMPLOYEES;

-- 9
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) LIKE ('%RE%')
INTERSECT
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'HR_REP';


-- Lab 4

-- 1
CREATE TABLE EMP_ANE AS SELECT * FROM EMPLOYEES;
CREATE TABLE DEPT_ANE AS SELECT * FROM DEPARTMENTS; 

-- 2
DESC EMPLOYEES;
DESC EMP_ANE;
DESC DEPARTMENTS;
DESC DEPT_ANE;

-- 3
SELECT *
FROM EMP_ANE;

SELECT *
FROM DEPT_ANE;

-- 4
ALTER TABLE EMP_ANE
ADD CONSTRAINT PK_EMP_ANE PRIMARY KEY(employee_id);

ALTER TABLE DEPT_ANE
ADD CONSTRAINT PK_DEPT_ANE PRIMARY KEY(department_id);

ALTER TABLE EMP_ANE
ADD CONSTRAINT FK_EMP_DEPT_ANE FOREIGN KEY(department_id) REFERENCES DEPT_ANE(department_id);

ALTER TABLE EMP_ANE ADD CONSTRAINT FK_EMP_EMP_ANE FOREIGN KEY(manager_id)
REFERENCES emp_pnu(employee_id);

ALTER TABLE DEPT_ANE
ADD CONSTRAINT FK_DEPT_EMP_ANE FOREIGN KEY(manager_id) REFERENCES EMP_PNU(employee_id);

-- 5
INSERT INTO DEPT_ANE (department_id, department_name, location_id)
VALUES (300, 'Programare', NULL);

COMMIT

-- 6
INSERT INTO EMP_ANE
VALUES (250, NULL, 'nume250', 'email250', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);

COMMIT

-- 7
INSERT INTO EMP_ANE (hire_date, job_id, employee_id, last_name, email, department_id)
VALUES (SYSDATE, 'sa_man', 278, 'nume_278', 'email_278', 300);

COMMIT

-- 8
CREATE TABLE EMP1_ANE AS SELECT * FROM EMPLOYEES;
DELETE FROM EMP1_ANE;

INSERT INTO EMP1_ANE
    SELECT *
    FROM EMPLOYEES
    WHERE commission_pct > 0.25;

SELECT * FROM EMP1_ANE;

-- 9
INSERT INTO EMP_ANE (employee_id, first_name, last_name, email, hire_date, job_id, salary)
VALUES(&cod, '&&prenume', '&&nume', substr('&prenume', 1, 1) || substr('&nume', 1, 7), SYSDATE, 'IT_PROG', &sal);
UNDEFINE prenume;
UNDEFINE nume;

SELECT * FROM EMP_ANE;

ROLLBACK;

-- 10
DELETE FROM EMP1_ANE;

CREATE TABLE EMP2_ANE AS SELECT * FROM EMPLOYEES;
DELETE FROM EMP2_ANE;

CREATE TABLE EMP3_ANE AS SELECT * FROM EMPLOYEES;
DELETE FROM EMP3_ANE;

INSERT ALL
    WHEN salary < 5000 THEN
        INTO EMP1_ANE
    WHEN salary BETWEEN 5000 AND 10000 THEN
        INTO EMP2_ANE
    ELSE
        INTO EMP3_ANE
SELECT * FROM EMPLOYEES;

SELECT * FROM EMP1_ANE;
SELECT * FROM EMP2_ANE;
SELECT * FROM EMP3_ANE;

ROLLBACK;

-- 11
CREATE TABLE EMP0_ANE AS SELECT * FROM EMPLOYEES;
DELETE FROM EMP0_ANE;

INSERT FIRST
    WHEN department_id = 80 THEN
        INTO EMP0_ANE
    WHEN salary < 5000 THEN
        INTO EMP1_ANE
    WHEN salary BETWEEN 5000 AND 10000 THEN
        INTO EMP2_ANE
    ELSE
        INTO EMP3_ANE
SELECT * FROM EMPLOYEES;

SELECT * FROM EMP0_ANE;
SELECT * FROM EMP1_ANE;
SELECT * FROM EMP2_ANE;
SELECT * FROM EMP3_ANE;

ROLLBACK;

-- 12
UPDATE EMP_ANE
SET salary = salary * 1.05;

SELECT * FROM EMP_ANE;

ROLLBACK;

-- 13
UPDATE EMP_ANE
SET job_id = 'SA_REP'
WHERE department_id = 80 AND commission_pct IS NOT NULL;

SELECT * FROM EMP_ANE;

ROLLBACK;

-- 14
SELECT *
FROM EMP_ANE
WHERE UPPER(last_name || first_name) = 'GRANTDOUGLAS'; --199

SELECT *
FROM DEPT_ANE
WHERE department_id = 20;

UPDATE DEPT_ANE
SET manager_id = (
                    SELECT employee_id
                    FROM EMP_ANE
                    WHERE UPPER(last_name || first_name) = 'GRANTDOUGLAS'
                 )
WHERE department_id = 20;

UPDATE EMP_ANE
SET salary = salary + 1000
WHERE UPPER(last_name || first_name) = 'GRANTDOUGLAS';

ROLLBACK;

-- 15
DELETE FROM DEPT_ANE;
SELECT * FROM DEPT_ANE;

-- 16
SELECT d.department_id
FROM EMPLOYEES e 
RIGHT JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
WHERE employee_id IS NULL;

DELETE FROM DEPT_ANE
WHERE department_id IN (
                            SELECT department_id
                            FROM DEPARTMENTS 
                            MINUS 
                            SELECT department_id
                            FROM EMPLOYEES
                       );

SELECT * FROM DEPT_ANE;

ROLLBACK;

-- 17
INSERT INTO DEPT_ANE
VALUES(320, 'DEPT_NOU', NULL, NULL);

SELECT * FROM dept_pnu;

-- 18
SAVEPOINT p;

-- 19
DELETE FROM DEPT_ANE
WHERE department_id BETWEEN 160 AND 200;

SELECT * FROM DEPT_ANE;

-- 20
ROLLBACK TO p;
COMMIT;

-- Lab 5

-- 1
CREATE TABLE ANGAJATI_ANE
(
    cod_ang NUMBER(4) CONSTRAINT PK_ANGAJAT PRIMARY KEY,
    nume VARCHAR2(20) CONSTRAINT NUME_ANGAJAT NOT NULL,
    prenume VARCHAR2(20),
    email CHAR(15) UNIQUE,
    data_ang DATE DEFAULT SYSDATE,
    job VARCHAR2(10),
    cod_sef NUMBER(4),
    salariu NUMBER(8, 2) NOT NULL,
    cod_dep NUMBER(2)
);

SELECT * FROM ANGAJATI_ANE;
DESC ANGAJATI_ANE;

DROP TABLE ANGAJATI_ANE;

-- 2
INSERT INTO ANGAJATI_ANE
VALUES(101, 'nume2', 'prenume2', 'nume2', to_date('02-02-2004','dd-mm-yyyy'), 'Inginer', 100, 10000, 10);

-- Lab 6

-- 1
SELECT last_name, hire_date
FROM EMPLOYEES
WHERE hire_date > (
                        SELECT hire_date
                        FROM EMPLOYEES
                        WHERE INITCAP(last_name) = 'Gates'
                  );

-- 2
SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE INITCAP(last_name) = 'Gates'
                       )
      AND INITCAP(last_name) != 'Gates';

SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE INITCAP(last_name) = 'King'
                       )
      AND INITCAP(last_name) != 'King';

-- 3
SELECT last_name, salary
FROM EMPLOYEES
WHERE manager_id = (
                        SELECT employee_id
                        FROM EMPLOYEES
                        WHERE manager_id IS NULL
                   );

-- 4
SELECT last_name, department_id, salary
FROM EMPLOYEES
WHERE (department_id, salary) IN (
                                    SELECT department_id, salary
                                    FROM EMPLOYEES
                                    WHERE commission_pct IS NOT NULL 
                                 );

-- 5
SELECT employee_id, last_name, salary
FROM EMPLOYEES
WHERE salary > (
                    SELECT AVG(salary)
                    FROM EMPLOYEES
               );

-- 6
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary + salary * NVL(commission_pct, 0) > (
                                                    SELECT MAX(salary)
                                                    FROM EMPLOYEES
                                                    WHERE UPPER(job_id) LIKE ('%CLERK')
                                                 )
ORDER BY salary DESC;

-- 7
SELECT last_name, department_name, salary
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
WHERE e.manager_id IN (
                        SELECT employee_id
                        FROM EMPLOYEES
                        WHERE commission_pct IS NULL
                   )
      AND commission_pct IS NOT NULL;

-- 8
SELECT last_name, department_id, job_id
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM DEPARTMENTS d
                            JOIN LOCATIONS l ON(d.location_id = l.location_id
                                                AND INITCAP(city) = 'Toronto')
                       );

-- 9
SELECT department_id
FROM DEPARTMENTS
WHERE department_id NOT IN ( 
                                SELECT department_id
                                FROM EMPLOYEES
                                WHERE department_id IS NOT NULL
                           );

SELECT department_id
FROM DEPARTMENTS
WHERE department_id NOT IN (
                                SELECT NVL(department_id, -1)
                                FROM EMPLOYEES
                           );

-- 10
INSERT INTO EMP_ANE (employee_id, last_name, email, hire_date, job_id, salary, commission_pct)
VALUES (252, 'Nume252', 'nume252@emp.com', SYSDATE, 'SA_REP', 5000, NULL);

SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
FROM EMP_ANE
WHERE employee_id = 252;

ROLLBACK;

INSERT INTO
    (SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct FROM EMP_ANE)
VALUES (252, 'Nume252', 'nume252@emp.com', SYSDATE, 'SA_REP', 5000, NULL);

SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
FROM EMP_ANE
WHERE employee_id = 252;

ROLLBACK;

-- 11
CREATE TABLE SUBALTERNI_ANE
(
    cod number(6) CONSTRAINT PK_SUBALTERNI PRIMARY KEY,
    nume VARCHAR2(25) CONSTRAINT SUBALTERNI_NUME NOT NULL,
    prenume VARCHAR(20),
    cod_manager number(6),
    nume_manager VARCHAR2(25) CONSTRAINT NUME_MANAGER NOT NULL
);

INSERT INTO SUBALTERNI_ANE(cod, nume, prenume, cod_manager, nume_manager)
(
    SELECT ang.employee_id, ang.last_name, ang.first_name, ang.manager_id, mg.last_name
    FROM EMPLOYEES ang
    JOIN EMPLOYEES mg ON(ang.manager_id = mg.employee_id)
    WHERE INITCAP(CONCAT(mg.last_name, mg.first_name)) = 'Kingsteven'
);

SELECT * FROM SUBALTERNI_ANE;
ROLLBACK;


-- Lab 7

-- 2
SELECT MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM EMPLOYEES;

-- 3
SELECT e.job_id, job_title, MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM EMPLOYEES e
JOIN JOBS j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title;

-- 4
SELECT NVL(TO_CHAR(department_id), 'Angajat fara departament'), COUNT(employee_id)
FROM EMPLOYEES
GROUP BY department_id;

-- 5
SELECT COUNT(DISTINCT manager_id) "Nr. manageri"
FROM EMPLOYEES;

-- 6
SELECT MAX(salary) - MIN(salary) Diferenta
FROM EMPLOYEES;

SELECT department_id, MAX(salary) - MIN(salary) Diferenta
FROM EMPLOYEES
WHERE department_id IS NOT NULL
GROUP BY department_id;

-- 7
SELECT department_name "Nume departament", d.location_id Locatie, COUNT(employee_id) "Nr. Angajati", ROUND(AVG(salary)) "Salariul mediu"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
JOIN LOCATIONS l ON(d.location_id = l.location_id)
GROUP BY department_name, d.location_id;

-- 8
SELECT employee_id, last_name
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
               )
ORDER BY salary DESC;

-- 9
SELECT manager_id, min(salary)
FROM EMPLOYEES
WHERE manager_id IS NOT NULL
GROUP BY manager_id
HAVING min(salary) > 1000
ORDER BY 2 DESC;

-- 10
SELECT e.department_id, department_name, max(salary)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY e.department_id, department_name
HAVING max(salary) >= 3000;

-- 11
SELECT MIN(ROUND(AVG(salary))) "Salariu mediu minim"
FROM EMPLOYEES
GROUP BY job_id;

-- 12
SELECT MAX(ROUND(AVG(salary))) "Salariu mediu maxim"
FROM EMPLOYEES
GROUP BY department_id;

-- 13
SELECT e.job_id, job_title, AVG(salary)
FROM EMPLOYEES e
JOIN JOBS j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title
HAVING ROUND(AVG(salary)) = (
                        SELECT MIN(ROUND(AVG(salary)))
                        FROM EMPLOYEES
                        GROUP BY job_id
                     );
-- 14
SELECT ROUND(AVG(salary))
FROM EMPLOYEES
HAVING AVG(salary) > 2500;

-- 15
SELECT department_id, job_id, SUM(salary)
FROM EMPLOYEES
GROUP BY department_id, job_id;

-- 16
SELECT d.department_id, department_name, COUNT(employee_id)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) < 4;


SELECT d.department_id, department_name, COUNT(employee_id)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) = (
                                SELECT MAX(COUNT(employee_id))
                                FROM EMPLOYEES
                                GROUP BY department_id
                            );

-- 17
SELECT COUNT(department_id)
FROM
(
    SELECT department_id, COUNT(employee_id) NrAngajati
    FROM EMPLOYEES
    GROUP BY department_id
)
WHERE NrAngajati > 15;

-- 18
SELECT department_id, SUM(salary)
FROM EMPLOYEES
WHERE department_id != 30
GROUP BY department_id
HAVING COUNT(employee_id) > 10
ORDER BY 1;

-- 19
SELECT jh.employee_id, CONCAT(last_name, ' ' || first_name)
FROM JOB_HISTORY jh
JOIN EMPLOYEES e ON(e.employee_id = jh.employee_id)
GROUP BY jh.employee_id, last_name, first_name
HAVING COUNT(jh.job_id) >= 2;

-- 20
SELECT ROUND(SUM(commission_pct) / COUNT(*), 2)
FROM EMPLOYEES;

-- 21
SELECT job_id Job, SUM(DECODE(department_id, 30, salary)) Dep30,
                   SUM(DECODE(department_id, 50, salary)) Dep50,
                   SUM(DECODE(department_id, 80, salary)) Dep80,
                   SUM(salary) Total
FROM EMPLOYEES
GROUP BY job_id;

SELECT job_id, 
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 30
                    AND job_id = e.job_id
              ) Dep30,
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 50
                    AND job_id = e.job_id
              ) Dep50,
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 80
                    AND job_id = e.job_id
              ) Dep80,
              SUM(salary) Total
FROM EMPLOYEES e
GROUP BY job_id;

-- 22
SELECT COUNT(employee_id) "Nr. Total Angajati", COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1997, employee_id)) "1997",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1998, employee_id)) "1998",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1998, employee_id)) "1999",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 2000, employee_id)) "2000"
FROM EMPLOYEES;

-- 23
SELECT e.department_id, department_name, SUM(salary)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY e.department_id, department_name;

SELECT d.department_id, department_name, a.suma
FROM DEPARTMENTS d
JOIN
(
    SELECT department_id, SUM(salary) suma
    FROM EMPLOYEES
    GROUP BY department_id
) a ON(a.department_id = d.department_id);

-- 24
SELECT last_name, salary, e.department_id, department_name, sal_med, nr_ang
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
JOIN 
(
    SELECT ROUND(AVG(salary)) sal_med, COUNT(employee_id) nr_ang, department_id
    FROM EMPLOYEES
    GROUP BY department_id
) ac ON (ac.department_id = e.department_id);

SELECT last_name, salary, e.department_id, department_name,
                                                            (
                                                                SELECT ROUND(AVG(salary))
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Salariu mediu",
                                                            (
                                                                SELECT COUNT(employee_id)
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Nr Angajati"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id);


-- Lab 8

-- 1
-- a)
SELECT last_name, salary, department_id
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
               );

-- b)
SELECT last_name, salary, department_id
FROM EMPLOYEES e
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
                    WHERE department_id = e.department_id
               );

-- c)
SELECT last_name, salary, e.department_id, department_name, 
                                                            (
                                                                SELECT ROUND(AVG(salary))
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Media salariilor",
                                                            (
                                                                SELECT COUNT(employee_id)
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Nr. Angajati"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id);

-- 2
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > ALL (
                        SELECT ROUND(AVG(salary))
                        FROM EMPLOYEES
                        GROUP BY department_id
                   );


SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(MAX(AVG(salary)))
                    FROM EMPLOYEES
                    GROUP BY department_id
               );

-- 3
SELECT last_name, salary, department_id
FROM EMPLOYEES e
WHERE salary = (
                    SELECT MIN(salary)
                    FROM EMPLOYEES
                    WHERE department_id = e.department_id
               );

-- 4
SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE salary = (
                                                SELECT MAX(salary)
                                                FROM EMPLOYEES
                                                WHERE department_id = 30
                                           )
                       );

-- 5
-- a)
SELECT employee_id, last_name, first_name
FROM EMPLOYEES
WHERE employee_id IN (
                        SELECT manager_id
                        FROM EMPLOYEES
                        GROUP BY manager_id
                        HAVING COUNT(employee_id) > 2
                    );

-- b)
SELECT employee_id, last_name, first_name,
                                           (
                                                SELECT COUNT(employee_id)
                                                FROM EMPLOYEES
                                                WHERE manager_id = e.employee_id
                                           ) "Nr subalterni"
FROM EMPLOYEES e;

-- 6
SELECT location_id
FROM LOCATIONS
INTERSECT
SELECT location_id
FROM DEPARTMENTS;

SELECT location_id
FROM LOCATIONS
WHERE location_id IN (
                        SELECT DISTINCT location_id  
                        FROM DEPARTMENTS
                     );

SELECT location_id
FROM LOCATIONS l
WHERE EXISTS (
                SELECT 'x'
                FROM DEPARTMENTS
                WHERE location_id = l.location_id
             );

-- 7
SELECT department_id, department_name
FROM DEPARTMENTS d
WHERE NOT EXISTS (
                    SELECT 'x'
                    FROM EMPLOYEES
                    WHERE department_id = d.department_id
                 );

-- 8
WITH 
val_dep AS 
(
    SELECT department_name, SUM(salary) AS total
    FROM DEPARTMENTS d
    JOIN EMPLOYEES e ON(d.department_id = e.department_id)
    GROUP BY department_name
),
val_medie AS 
(
    SELECT SUM(total) / COUNT(*) AS medie
    FROM val_dep
)
SELECT *
FROM val_dep
WHERE total > 
              (
                SELECT medie
                FROM val_medie
              )
ORDER BY department_name;

-- 9
WITH
subord_SK AS
(
    SELECT employee_id, first_name, last_name, hire_date
    FROM EMPLOYEES
    WHERE manager_id IN (
                            SELECT employee_id
                            FROM EMPLOYEES  
                            WHERE INITCAP(CONCAT(first_name, last_name)) = 'Stevenking'
                        )
         AND TO_CHAR(hire_date, 'YYYY') != '1970'
)
SELECT employee_id, first_name, last_name, hire_date
FROM subord_SK
WHERE hire_date = (
                    SELECT MIN(hire_date)
                    FROM subord_SK
                  );

-- 10
SELECT employee_id, last_name, salary, rownum
FROM 
(
    SELECT employee_id, salary, last_name
    FROM EMPLOYEES
    ORDER BY salary DESC
)
WHERE rownum <= 10
ORDER BY salary;

-- 11
SELECT employee_id, last_name, first_name, salary, rownum
FROM
(
    SELECT employee_id, last_name, first_name, salary
    FROM EMPLOYEES
    ORDER BY salary DESC
)
WHERE rownum <= 3
ORDER BY salary DESC;

-- 12
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(manager_id), 'nimeni') || ' si ' ||
                                                                CASE (
                                                                            SELECT COUNT(employee_id)
                                                                            FROM EMPLOYEES 
                                                                            WHERE department_id = d.department_id
                                                                     )
                                                                WHEN 0 THEN 'nu are salariati'
                                                                ELSE 'are numarul de salariati ' || TO_CHAR((
                                                                            SELECT COUNT(employee_id)
                                                                            FROM EMPLOYEES 
                                                                            WHERE department_id = d.department_id
                                                                     ))
                                                                END "Informatii"
FROM DEPARTMENTS d;

-- 13
SELECT CASE LENGTH(last_name)
WHEN LENGTH(first_name) THEN last_name || ' ' || first_name
ELSE last_name || ' ' || first_name || ' ' || LENGTH(first_name)
END "Informatii"
FROM EMPLOYEES e;

-- 14
SELECT last_name, hire_date, salary, 
                                    CASE TO_CHAR(hire_date, 'yyyy')
                                        WHEN '1989' THEN salary * 1.20
                                        WHEN '1990' THEN salary * 1.15
                                        WHEN '1991' THEN salary * 1.10
                                        ELSE salary
                                    END "Salariu marit"
FROM EMPLOYEES;

-- 15
-- a)
SELECT job_title, CASE SUBSTR(job_title, 1, 1)
            WHEN 'S' THEN (
                            SELECT SUM(salary)
                            FROM EMPLOYEES
                            WHERE job_id = j.job_id
                          )
            ELSE 0
       END "Suma salariilor"
FROM JOBS j
ORDER BY 1 DESC;

-- b)
SELECT job_id, ROUND(AVG(salary))
FROM EMPLOYEES
GROUP BY job_id
HAVING SUM(salary) = (
                    SELECT MAX(SUM(salary))
                    FROM EMPLOYEES
                    GROUP BY job_id
                );

-- c)


-- Lab 9
SELECT DISTINCT employee_id
FROM WORKS_ON a
WHERE NOT EXISTS (
                    SELECT 'x'
                    FROM PROJECT p
                    WHERE budget = 10000
                    AND NOT EXISTS
                                    (
                                        SELECT 'x'
                                        FROM WORKS_ON b
                                        WHERE p.project_id = b.project_id
                                        AND b.employee_id = a.employee_id
                                    )
                 );

SELECT employee_id
FROM WORKS_ON
WHERE project_id IN (
                        SELECT project_id
                        FROM PROJECT
                        WHERE budget = 10000
                    )
GROUP BY employee_id
HAVING COUNT(project_id) = (
                                SELECT COUNT(*)
                                FROM project
                                WHERE budget = 10000
                           );

-- 1
SELECT * FROM PROJECT;
SELECT * FROM WORKS_ON;

SELECT employee_id
FROM WORKS_ON


-- 9
select employee_id
from works_on
where project_id IN (select project_id
                      from project
                      where project_manager = 102)--proiectele conduse de 102 -> p1 si p3


MINUS --eliminam angajatii care lucreaza la proiecte conduse de un alt manager
select employee_id
from works_on
where project_id NOT IN (select project_id
    from project
    where project_manager = 102);


-- 1
select sa.cod_asigurator, nume_societate, t.cod_timbru, nume, data_emitere, t.valoarefrom soc_asigurare sa join este_asigurat ea on (sa.cod_asigurator = ea.cod_asigurator)join timbru t on (ea.cod_timbru = t.cod_timbru)where to_char(data_emitere, 'yyyy') = 1990order by t.valoare;

-- 2
select sa.cod_asigurator, nume_societate, tara, cod_timbru,(select sum(valoare)from este_asigurat x join soc_asigurare y on(x.cod_asigurator = y.cod_asigurator)where sa.tara = y.tara) "Valoare totala"from soc_asigurare sa join este_asigurat ea on (sa.cod_asigurator = ea.cod_asigurator);

-- 3
select numefrom (select vanz.cod_vanzator, nume, count(cod_timbru)from vinde vin join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator)group by vanz.cod_vanzator, numeorder by 3 desc)where rownum <= 2

-- 4
with valoare_totala as (select vanz.cod_vanzator, vanz.nume, sum(val_cumparare) sumafrom vinde vin join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator)group by vanz.cod_vanzator, vanz.nume),vanzatori as (select nume, sumafrom valoare_totalawhere suma > (select round(avg(suma))from valoare_totala))select *from vanzatori;

-- 5
select cod_asiguratorfrom este_asiguratwhere cod_timbru IN (select cod_timbrufrom timbruwhere to_char(data_emitere, 'yyyy') = 1990)group by cod_asiguratorhaving count(cod_timbru) = (select count(cod_timbru)from timbruwhere to_char(data_emitere, 'yyyy') = 1990);

-- 6
select sum(t.valoare), count(t.cod_timbru)from timbru t join vinde v on (t.cod_timbru = v.cod_timbru)where val_pornire = val_cumparare and to_char(data_achizitie, 'yyyy') = 2020;

-- 7
create table valoare_totala(nume_timbru varchar2(30),nume_vanzator varchar2(30),numar_total_timbre number(5));

insert into valoare_totala (select t.nume, vanz.nume, (select count(*)from vindewhere cod_timbru = t.cod_timbru) "Timbre vandute"from timbru t join vinde vin on (t.cod_timbru = vin.cod_timbru)join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator));select * from valoare_totala;