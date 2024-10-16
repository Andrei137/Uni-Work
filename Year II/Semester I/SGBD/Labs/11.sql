-- 1
CREATE OR REPLACE TRIGGER trig1_ane
    BEFORE INSERT OR UPDATE OR DELETE ON emp_ane
    FOR EACH ROW
    FOLLOWS trig21_ane
BEGIN
    IF (TO_CHAR(SYSDATE,'D') = 3)
        OR (TO_CHAR(SYSDATE,'HH24') NOT BETWEEN 8 AND 20) THEN
        RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
    END IF;
END;
/
DELETE FROM emp_ane;
/
ROLLBACK;
/
DROP TRIGGER trig1_ane;

-- 2
CREATE OR REPLACE TRIGGER trig21_ane
    BEFORE UPDATE OF salary ON emp_ane
    FOR EACH ROW
BEGIN
    IF (:NEW.salary < :OLD.salary) THEN
        RAISE_APPLICATION_ERROR(-20002,'salariul nu poate fi micsorat');
    END IF;
END;
/
UPDATE emp_ane
SET salary = salary - 100;
/
DROP TRIGGER trig21_ane;

-- Inserts
CREATE TABLE info_dept_ane
(id NUMBER PRIMARY KEY,
nume_dept VARCHAR2(100),
plati NUMBER);

INSERT INTO info_dept_ane
SELECT department_id, department_name, SUM(salary)
FROM departments join employees USING(department_id)
GROUP BY department_id, department_name;

SELECT *
FROM info_dept_ane;

ALTER TABLE info_dept_ane
ADD numar NUMBER;
UPDATE info_dept_ane i
SET numar = (SELECT COUNT(*) FROM employees WHERE i.id = department_id);

CREATE TABLE info_emp_ane
(id NUMBER PRIMARY KEY,
nume VARCHAR2(100),
salariu NUMBER,
id_dept NUMBER REFERENCES info_dept_ane(id));

INSERT into info_emp_ane
SELECT employee_id, last_name, salary, department_id
FROM employees;


-- 4
CREATE OR REPLACE PROCEDURE modific_plati_ane
    (v_codd info_dept_ane.id%TYPE,
    v_plati info_dept_ane.plati%TYPE) AS
BEGIN
    UPDATE info_dept_ane
    SET plati = NVL (plati, 0) + v_plati
    WHERE id = v_codd;
END;
/
CREATE OR REPLACE TRIGGER trig4_ane
    AFTER DELETE OR UPDATE OR INSERT OF salary ON emp_ane
    FOR EACH ROW
BEGIN
    IF DELETING THEN
        -- se sterge un angajat
        modific_plati_ane(:OLD.department_id, -1*:OLD.salary);
    ELSIF UPDATING THEN
        --se modifica salariul unui angajat
        modific_plati_ane(:OLD.department_id,:NEW.salary-:OLD.salary);
    ELSE
        -- se introduce un nou angajat
        modific_plati_ane(:NEW.department_id, :NEW.salary);
    END IF;
END;
/
SELECT * FROM info_dept_ane WHERE id=90;

INSERT INTO emp_ane (employee_id, last_name, email, hire_date, job_id, salary, department_id)
VALUES (300, 'N1', 'n1@g.com', sysdate, 'SA_REP', 2000, 90);

CREATE OR REPLACE TRIGGER trigE1_ane
    BEFORE DELETE ON dept_ane
BEGIN
    IF UPPER(USER) = UPPER('Grupa252') THEN
        RAISE_APPLICATION_ERROR(-20003, 'Utilizatorul nu are dreptul sa stearga');
    END IF;
END;
/
DELETE FROM dept_ane
WHERE department_id = 100;
/
ROLLBACK
/
CREATE OR REPLACE TRIGGER trigE2_ane
    BEFORE INSERT OR UPDATE OF commission_pct ON emp_ane
    FOR EACH ROW
BEGIN
    IF (:NEW.commission_pct >= 0.5) THEN
        RAISE_APPLICATION_ERROR(-20002,'comisionul nu poate fi marit');
    END IF;
END;
/
UPDATE emp_ane
SET commission_pct = 0.51;
/
ROLLBACK
/
CREATE OR REPLACE PROCEDURE modific_numar_ane
    (v_departament_id info_dept_ane.id%TYPE,
     v_modificare info_dept_ane.numar%TYPE) AS
BEGIN
    UPDATE info_dept_ane
    SET numar = numar + v_modificare
    WHERE id = v_departament_id;
END;
/
CREATE OR REPLACE TRIGGER trigE3_ane
    AFTER DELETE OR UPDATE OR INSERT OF id_dept ON info_emp_ane
    FOR EACH ROW
BEGIN
    IF DELETING THEN
        modific_numar_ane(:OLD.id_dept, -1);
    ELSIF UPDATING THEN
        modific_numar_ane(:OLD.id_dept, -1);
        modific_numar_ane(:NEW.id_dept, 1);
    ELSE
        modific_numar_ane(:NEW.id_dept, 1);
    END IF;
END;
/
DROP TRIGGER trigE3_ane;

SELECT * FROM info_dept_ane;

INSERT INTO info_emp_ane (id, nume, salariu, id_dept)
VALUES (303, 'N1', 2000, 90);
