DECLARE
    v_nume employees.last_name%TYPE := Initcap('&p_nume');
FUNCTION f1 RETURN NUMBER IS
    salariu employees.salary%type;
BEGIN
    SELECT salary INTO salariu
    FROM employees
    WHERE last_name = v_nume;
    RETURN salariu;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');
        RETURN -20001;
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Alta eroare!');
    END f1;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este '|| f1);
END;


CREATE OR REPLACE FUNCTION f2_ane
    (v_nume employees.last_name%TYPE DEFAULT 'King')
RETURN NUMBER IS
    salariu employees.salary%type;
BEGIN
    SELECT salary INTO salariu
    FROM employees
    WHERE last_name = v_nume;
    RETURN salariu;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20002, 'Alta eroare!');
END f2_ane;
/

CREATE TABLE info_ane
(
    id NUMBER(10) PRIMARY KEY,
    utilizator VARCHAR2(100),
    data DATE,
    comanda VARCHAR2(500),
    nr_linii NUMBER(10),
    eroare VARCHAR2(100)
);

CREATE SEQUENCE info_ane_seq
START WITH 1
INCREMENT BY 1
MAXVALUE 99999999
NOCYCLE;

CREATE OR REPLACE FUNCTION f3_ane
(
    v_nume employees.last_name%TYPE DEFAULT 'Bell'
)
RETURN NUMBER IS
    salariu employees.salary%TYPE;
    v_user info_ane.utilizator%TYPE;
    v_nr_linii info_ane.nr_linii%TYPE;
    v_mesaj info_ane.eroare%TYPE;
BEGIN
    SELECT user 
    INTO v_user
    FROM dual;

    SELECT salary INTO salariu
    FROM employees
    WHERE last_name = v_nume;

    SELECT COUNT(*)
    INTO v_nr_linii
    FROM employees
    WHERE last_name = v_nume;
    
    v_mesaj := 'Totul a mers ok';
    INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
    RETURN salariu;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
        RETURN -20000;
    WHEN TOO_MANY_ROWS THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
        RETURN -20001;
    WHEN OTHERS THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval,v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
        RETURN -20002;
END f3_ane;
/
BEGIN 
    DBMS_OUTPUT.PUT_LINE(f3_ane('Kochhar'));
END;
/
SELECT * FROM info_ane;


CREATE OR REPLACE PROCEDURE p4_ane
(v_nume employees.last_name%TYPE)
IS
    salariu employees.salary%TYPE;
    v_user info_ane.utilizator%TYPE;
    v_nr_linii info_ane.nr_linii%TYPE;
    v_mesaj info_ane.eroare%TYPE;
BEGIN
    SELECT user 
    INTO v_user
    FROM dual;

    SELECT salary INTO salariu
    FROM employees
    WHERE last_name = v_nume;

    SELECT COUNT(*)
    INTO v_nr_linii
    FROM employees
    WHERE last_name = v_nume;
    
    v_mesaj := 'Totul a mers ok';
    INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
    WHEN TOO_MANY_ROWS THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
    WHEN OTHERS THEN
        v_mesaj := SQLCODE||SUBSTR(SQLERRM, 1, 50);
        INSERT INTO info_ane VALUES(info_ane_seq.nextval,v_user, sysdate, 'SELECT '||v_nume, v_nr_linii, v_mesaj);
END p4_ane;
/
BEGIN
    p4_ane('Bell');
END;
/
SELECT * FROM info_ane;


CREATE OR REPLACE FUNCTION f4_ane
    (v_oras locations.city%TYPE DEFAULT 'Seattle') RETURN NUMBER
IS
    TYPE tablou_imbricat IS TABLE OF employees.last_name%TYPE;
    nume_angajati tablou_imbricat := tablou_imbricat();
    v_user info_ane.utilizator%TYPE;
    v_nr_linii info_ane.nr_linii%TYPE := 0;
    v_mesaj info_ane.eroare%TYPE;
    v_nr NUMBER;
BEGIN
    SELECT user 
    INTO v_user
    FROM dual;

    SELECT COUNT(*)
    INTO v_nr
    FROM locations
    WHERE INITCAP(city) = INITCAP(v_oras);

    IF v_nr = 0 THEN
        v_mesaj := 'Nu exista orasul dat ca parametru!';
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||user, v_nr_linii, v_mesaj);
        RETURN -20001;
    END IF;

    SELECT last_name
    BULK COLLECT INTO nume_angajati
    FROM employees e
    JOIN departments d ON(e.department_id = d.department_id)
    JOIN locations l ON(d.location_id = l.location_id)
    WHERE employee_id IN (
                            SELECT employee_id
                            FROM job_history
                            GROUP BY employee_id
                            HAVING COUNT(*) = 2
                     )
    AND INITCAP(city) LIKE INITCAP(v_oras);
    
    IF NOT nume_angajati.EXISTS(1) THEN
        v_mesaj := 'Nu exista angajat din orasul dat';
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||user, v_nr_linii, v_mesaj);
        RETURN -20000;
    END IF;
    FOR i IN nume_angajati.FIRST..nume_angajati.LAST LOOP
        SELECT COUNT(*)
        INTO v_nr_linii
        FROM employees
        WHERE last_name = nume_angajati(i);

         v_mesaj := 'Totul a mers ok';
        INSERT INTO info_ane VALUES(info_ane_seq.nextval, v_user, sysdate, 'SELECT '||nume_angajati(i), v_nr_linii, v_mesaj);
    END LOOP;
    RETURN 0;
END f4_ane;
/
BEGIN 
    DBMS_OUTPUT.PUT_LINE(f4_ane('Sinaia')); -- nu exista orasul
    DBMS_OUTPUT.PUT_LINE(f4_ane('Roma')); -- nu exista angajat din acest oras
    DBMS_OUTPUT.PUT_LINE(f4_ane('Seattle')); -- exista 2 angajati din acest oras
END;
/
SELECT * FROM info_ane;
