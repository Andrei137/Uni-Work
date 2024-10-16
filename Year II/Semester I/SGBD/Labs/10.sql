CREATE SEQUENCE emp_seq
INCREMENT BY 1
START WITH 1
MAXVALUE 999
NOCYCLE;
/
CREATE OR REPLACE PACKAGE pachet_E1_ANE AS
    PROCEDURE p_emp(nume emp_ane.last_name%TYPE,
                    prenume emp_ane.first_name%TYPE,
                    email emp_ane.email%TYPE,
                    telefon emp_ane.phone_number%TYPE,
                    nume_manager emp_ane.last_name%TYPE, 
                    prenume_manager emp_ane.first_name%TYPE,
                    nume_dept departments.department_name%TYPE,
                    titlu_job jobs.job_title%TYPE
                    );
         
    FUNCTION find_salary(cod_dept departments.department_id%TYPE, cod_job jobs.job_id%TYPE)
        RETURN emp_ane.salary%TYPE;
    FUNCTION get_cod_mgr(nume emp_ane.last_name%TYPE, prenume emp_ane.first_name%TYPE)
        RETURN emp_ane.manager_id%TYPE;
    FUNCTION get_cod_dept(nume_dept departments.department_name%TYPE)
        RETURN departments.department_id%TYPE;
    FUNCTION get_cod_job(titlu_job jobs.job_title%TYPE)
        RETURN jobs.job_id%TYPE;
END pachet_E1_ANE;
/
CREATE OR REPLACE PACKAGE BODY pachet_E1_ANE AS
    FUNCTION get_cod_job(titlu_job jobs.job_title%TYPE)
        RETURN jobs.job_id%TYPE IS
        cod_job jobs.job_id%TYPE := '-1';
    BEGIN
        SELECT job_id INTO cod_job
        FROM jobs
        WHERE UPPER(job_title) = UPPER(titlu_job);
        RETURN cod_job;
    END get_cod_job;
    
    FUNCTION get_cod_dept(nume_dept departments.department_name%TYPE)
        RETURN departments.department_id%TYPE IS
        cod_dept departments.department_id%TYPE := -1;
    BEGIN
        SELECT department_id 
        INTO cod_dept
        FROM departments
        WHERE UPPER(department_name) = UPPER(nume_dept);
        RETURN cod_dept;
    END get_cod_dept;

    FUNCTION get_cod_mgr(nume emp_ane.last_name%TYPE, prenume emp_ane.first_name%TYPE)
        RETURN emp_ane.manager_id%TYPE IS
        cod_mgr emp_ane.manager_id%TYPE := -1;
    BEGIN
        SELECT employee_id 
        INTO cod_mgr
        FROM emp_ane
        WHERE UPPER(last_name) = UPPER(nume) AND UPPER(first_name) = UPPER(prenume);
        RETURN cod_mgr;
    END get_cod_mgr;

    FUNCTION find_salary(cod_dept departments.department_id%TYPE, cod_job jobs.job_id%TYPE)
        RETURN emp_ane.salary%TYPE IS
        salariu emp_ane.salary%TYPE;
    BEGIN
        SELECT MIN(salary) INTO salariu
        FROM employees
        WHERE department_id = cod_dept AND job_id = cod_job;
        RETURN salariu;
    END find_salary;

    PROCEDURE p_emp(nume emp_ane.last_name%TYPE,
                    prenume emp_ane.first_name%TYPE,
                    email emp_ane.email%TYPE,
                    telefon emp_ane.phone_number%TYPE,
                    nume_manager emp_ane.last_name%TYPE, 
                    prenume_manager emp_ane.first_name%TYPE,
                    nume_dept departments.department_name%TYPE,
                    titlu_job jobs.job_title%TYPE
                    ) IS
        cod_dept departments.department_id%TYPE;
        cod_job jobs.job_id%TYPE;
        cod_mgr emp_ane.manager_id%TYPE;
        salariu employees.salary%TYPE;
    BEGIN
        cod_dept := get_cod_dept(nume_dept);
        IF cod_dept = -1 THEN
            RAISE_APPLICATION_ERROR(-20001, 'Nu exista departamentul');
        END IF;

        cod_job := get_cod_job(titlu_job);
        IF cod_job = '-1' THEN
            RAISE_APPLICATION_ERROR(-20002, 'Nu exista job-ul');
        END IF;
        
        cod_mgr := get_cod_mgr(nume_manager, prenume_manager);
        IF cod_mgr = -1 THEN
            RAISE_APPLICATION_ERROR(-20003, 'Nu exista managerul');
        END IF;

        salariu := find_salary(cod_dept, cod_job);
        INSERT INTO emp_ane
        VALUES(emp_seq.NEXTVAL, nume, prenume, email, telefon, SYSDATE, cod_job, salariu, NULL, cod_mgr, cod_dept);
    END p_emp;
END;
/
BEGIN
    pachet_E1_ANE.p_emp('Buzatu', 'Giulian', 'buzatu.giulian@yahoo.com', '0754641082', 'King', 'Steven', 'IT', 'Programmer');
END;
/
SELECT * FROM emp_ane
WHERE last_name = 'Buzatu' AND first_name = 'Giulian';
/
ROLLBACK;