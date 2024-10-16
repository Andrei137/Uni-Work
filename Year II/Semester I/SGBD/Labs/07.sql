-- 10 cursor clasic
DECLARE
    CURSOR c_dept IS
        SELECT department_id, department_name
        FROM departments
        WHERE department_id IN (10,20,30,40);
    
    CURSOR c_emp IS
        SELECT department_id, last_name
        FROM employees;
        
    TYPE rec1 IS RECORD(id employees.department_id%TYPE, name employees.last_name%TYPE);
    TYPE rec2 IS RECORD(id departments.department_id%TYPE, name departments.department_name%TYPE);
    v_emp rec1;
    v_dept rec2;
BEGIN
    OPEN c_dept;
    LOOP
        FETCH c_dept INTO v_dept;
        EXIT WHEN c_dept%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('DEPARTAMENT '||v_dept.name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        
        OPEN c_emp;
        LOOP
            FETCH c_emp INTO v_emp;
            EXIT WHEN c_emp%NOTFOUND;
            if v_dept.id = v_emp.id THEN
                DBMS_OUTPUT.PUT_LINE(v_emp.name);
            END IF;
        END LOOP;
        CLOSE c_emp;
    END LOOP;
    CLOSE c_dept;
END;
/

-- 10 ciclu cursor
DECLARE
    CURSOR c_dept IS
        SELECT department_id, department_name
        FROM departments
        WHERE department_id IN (10,20,30,40);
    
    CURSOR c_emp IS
        SELECT department_id, last_name
        FROM employees;
BEGIN
    FOR v_dept IN c_dept
    LOOP
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('DEPARTAMENT '||v_dept.department_name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        FOR v_emp IN c_emp
        LOOP
            if v_dept.department_id = v_emp.department_id THEN
                DBMS_OUTPUT.PUT_LINE(v_emp.last_name);
            END IF;
        END LOOP;
    END LOOP;
END;
/

-- E1
-- cursor clasic
DECLARE
    CURSOR c_job IS (
                        SELECT job_id, job_title 
                        FROM jobs
                    );
    
    CURSOR c_emp IS (
                        SELECT job_id, last_name, salary
                        FROM employees
                    );
        
    TYPE rec1 IS RECORD(id employees.job_id%TYPE, name employees.last_name%TYPE, salary employees.salary%TYPE);
    TYPE rec2 IS RECORD(id jobs.job_id%TYPE, name jobs.job_title%TYPE);
    v_emp rec1;
    v_job rec2;
BEGIN
    OPEN c_job;
    LOOP
        FETCH c_job INTO v_job;
        EXIT WHEN c_job%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('JOB '||v_job.name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        OPEN c_emp;
        IF c_emp%NOTFOUND THEN
            DBMS_OUTPUT.PUT_LINE('JOBUL '||v_job.name||' nu are angajati');
        ELSE
            LOOP
                FETCH c_emp INTO v_emp;
                EXIT WHEN c_emp%NOTFOUND;
                IF v_job.id = v_emp.id THEN
                   DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_emp.name || ' cu salariul '||v_emp.salary || 'si numar de ordine '|| c_emp%ROWCOUNT);
                END IF;
            END LOOP;
        END IF;
        CLOSE c_emp;
    END LOOP;
    CLOSE c_job;
END;
/

-- ciclu cursor
DECLARE
    CURSOR c_job IS
        SELECT job_id, job_title
        FROM jobs;
    
    CURSOR c_emp IS
        SELECT job_id, last_name, salary
        FROM employees;
BEGIN
    FOR v_job IN c_job
    LOOP
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('JOB '||v_job.job_title);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        FOR v_emp IN c_emp
        LOOP
            if v_job.job_id = v_emp.job_id THEN
                DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_emp.last_name || ' cu salariul '||v_emp.salary);
            END IF;
        END LOOP;
    END LOOP;
END;
/

-- ciclu cursor cu subcereri
BEGIN
    FOR v_job IN (
                    SELECT job_id, job_title
                    FROM jobs
                  )
    LOOP
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('JOB '||v_job.job_title);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        FOR v_emp IN (
                        SELECT last_name, salary
                        FROM employees
                        WHERE job_id = v_job.job_id
                      )
        LOOP
            DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_emp.last_name || ' cu salariul '||v_emp.salary);
        END LOOP;
    END LOOP;
END;
/

-- expresii cursor
DECLARE
    TYPE refcursor IS REF CURSOR;
    CURSOR c_job IS
        SELECT job_title,
            CURSOR (
                        SELECT last_name, salary
                        FROM employees e
                        WHERE e.job_id = j.job_id
                    )
        FROM jobs j;
    v_nume_job jobs.job_title%TYPE;
    v_cursor refcursor;
    v_nume_emp employees.last_name%TYPE;
    v_salariu_emp employees.salary%TYPE;
BEGIN
    OPEN c_job;
    LOOP
        FETCH c_job INTO v_nume_job, v_cursor;
        EXIT WHEN c_job%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE('JOB '||v_nume_job);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        LOOP
            FETCH v_cursor INTO v_nume_emp, v_salariu_emp;
            EXIT WHEN v_cursor%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_nume_emp || ' cu salariul '|| v_salariu_emp);
        END LOOP;
    END LOOP;
    CLOSE c_job;
END;
/

DECLARE
    TYPE emp_tip IS REF CURSOR RETURN employees%ROWTYPE;
    -- sau
    -- TYPE emp_tip IS REF CURSOR;
    v_emp emp_tip;
    v_optiune NUMBER := &p_optiune;
    v_ang employees%ROWTYPE;
BEGIN
    IF v_optiune = 1 THEN
        OPEN v_emp FOR SELECT *
        FROM employees;
    ELSIF v_optiune = 2 THEN
        OPEN v_emp FOR SELECT *
        FROM employees
        WHERE salary BETWEEN 10000 AND 20000;
    ELSIF v_optiune = 3 THEN
        OPEN v_emp FOR SELECT *
                       FROM employees
                       WHERE TO_CHAR(hire_date, 'YYYY') = 2000;
    ELSE
    DBMS_OUTPUT.PUT_LINE('Optiune incorecta');
    END IF;
    IF v_emp%ISOPEN THEN
        LOOP
        FETCH v_emp into v_ang;
        EXIT WHEN v_emp%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_ang.last_name);
        END LOOP;
        DBMS_OUTPUT.PUT_LINE('Au fost procesate '||v_emp%ROWCOUNT
        || ' linii');
        CLOSE v_emp;
    END IF;
END;
/

DECLARE
    TYPE empref IS REF CURSOR;
    v_emp empref;
    v_nr INTEGER := &n;
    v_cod employees.employee_id%TYPE;
    v_sal employees.salary%TYPE;
    v_comm employees.commission_pct%TYPE;

BEGIN
    OPEN v_emp FOR
    'SELECT employee_id, salary, commission_pct ' ||
    'FROM employees WHERE salary > :bind_var'
    USING v_nr;
    LOOP
        FETCH v_emp INTO v_cod, v_sal, v_comm;
        EXIT WHEN v_emp%NOTFOUND;
        
        IF v_comm IS NOT NULL THEN
             DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_cod || ' cu salariul '|| v_sal||' si comisionul '||v_comm);
        ELSE
            DBMS_OUTPUT.PUT_LINE ('Angajatul '|| v_cod || ' cu salariul '|| v_sal||' si comisionul -1');
        END IF;
    END LOOP;
    CLOSE v_emp;
END;
/
