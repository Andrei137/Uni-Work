-- E1 Varianta 1
DECLARE
    TYPE rec IS RECORD(id emp_ane.employee_id%TYPE, salariu emp_ane.salary%TYPE);
    TYPE tablou_indexat IS TABLE OF rec
                INDEX BY PLS_INTEGER;
    ang_pr_plat tablou_indexat;
BEGIN
    SELECT *
    BULK COLLECT INTO ang_pr_plat
    FROM
    (
        SELECT employee_id, salary
        FROM emp_ane
        WHERE COMMISSION_PCT IS NULL
        ORDER BY salary
    )
    WHERE ROWNUM<=5; 
    
    FOR i IN ang_pr_plat.first..ang_pr_plat.last LOOP
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| ang_pr_plat(i).salariu);
        UPDATE emp_ane
        SET salary = salary * 1.05
        WHERE employee_id = ang_pr_plat(i).id;   
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| ang_pr_plat(i).salariu * 1.05|| chr(10));
    END LOOP;
END;
/
ROLLBACK;

-- E1 Varianta 2
DECLARE
    TYPE tablou_imbricat IS TABLE OF emp_ane%ROWTYPE;
    ang_pr_plat tablou_imbricat := tablou_imbricat();
BEGIN
    SELECT *
    BULK COLLECT INTO ang_pr_plat
    FROM
    (
        SELECT *
        FROM emp_ane
        WHERE COMMISSION_PCT IS NULL
        ORDER BY salary
    )
    WHERE ROWNUM<=5; 
    
    FOR i IN ang_pr_plat.first..ang_pr_plat.last LOOP
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| ang_pr_plat(i).salary);
        UPDATE emp_ane
        SET salary = salary * 1.05
        WHERE employee_id = ang_pr_plat(i).employee_id;   
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| ang_pr_plat(i).salary * 1.05|| chr(10));
    END LOOP;
END;
/
ROLLBACK;

-- E1 Varianta 3
DECLARE
    TYPE vector IS VARRAY(5) OF NUMBER;
    salariu vector := vector();
    cod vector := vector();
BEGIN
    SELECT *
    BULK COLLECT INTO salariu, cod
    FROM
    (
        SELECT salary, employee_id
        FROM emp_ane
        WHERE COMMISSION_PCT IS NULL
        ORDER BY salary
    )
    WHERE ROWNUM<=5; 
    
    FOR i IN salariu.first..salariu.last LOOP
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| salariu(i));
        UPDATE emp_ane
        SET salary = salary * 1.05
        WHERE employee_id = cod(i);   
        DBMS_OUTPUT.PUT_LINE('Valoarea veche '|| salariu(i) * 1.05|| chr(10));
    END LOOP;
END;
/
ROLLBACK;

-- E2
CREATE OR REPLACE TYPE tip_orase_ane IS TABLE OF VARCHAR2(64);
/
CREATE TABLE excursie_ane
(
    cod_excursie NUMBER(4),
    denumire VARCHAR2(20),
    orase tip_orase_ane,
    status VARCHAR2(20)
) NESTED TABLE orase STORE AS tab_orase_ane;


DECLARE
    CURSOR c IS
    SELECT id_client, NVL(nr_facturi_neachitate, 0), NVL(nr_facturi_achitate, 0), email
    FROM
    (
        SELECT id_client, COUNT(*) AS nr_facturi_neachitate
        FROM facturi
        WHERE UPPER(status) LIKE 'NEACHITAT'
        GROUP BY id_client
    )
    FULL OUTER JOIN
    (
        SELECT id_client, COUNT(*) AS nr_facturi_achitate
        FROM facturi
        WHERE UPPER(status) LIKE 'ACHITAT'
        GROUP BY id_client
    ) USING(id_client)
    JOIN clienti USING(id_client);
BEGIN
    OPEN c;
    FETCH c INTO



DROP TABLE excursie_ane;
DROP TYPE tip_orase_ane;

CREATE OR REPLACE TYPE tip_orase_ane AS TABLE OF VARCHAR2(64);
/
CREATE TABLE excursie_ane
(
    cod_excursie NUMBER(4),
    denumire VARCHAR2(20),
    orase tip_orase_ane,
    status VARCHAR2(20)
) NESTED TABLE orase STORE as orase2_ane;

-- a
INSERT INTO excursie_ane VALUES (1,'interna',tip_orase_ane('Ploiesti','Azuga','Brasov'), 'disponibila');
INSERT INTO excursie_ane VALUES (2,'munte', tip_orase_ane('Sinaia','Brasov','Azuga'), 'disponibila');
INSERT INTO excursie_ane VALUES (3,'mare', tip_orase_ane('Mamaia','Costinesti','Eforie Nord'), 'indisponibila');
INSERT INTO excursie_ane VALUES (4,'strainatate',tip_orase_ane('Budapesta','Belgrad','Madrid'), 'indisponibila');
INSERT INTO excursie_ane VALUES (5,'asia',tip_orase_ane('China','Japonia'), 'disponibila');

/*
b. Actualizați coloana orase pentru o excursie specificată:
- adăugați un oraș nou în listă, ce va fi ultimul vizitat în excursia respectivă;
- adăugați un oraș nou în listă, ce va fi al doilea oraș vizitat în excursia respectivă;
- inversați ordinea de vizitare a două dintre orașe al căror nume este specificat;
- eliminați din listă un oraș al cărui nume este specificat.
 */

-- b
DEFINE p_cod = 1
DECLARE
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
BEGIN
    SELECT orase 
    INTO v_orase
    FROM excursie_ane
    WHERE cod_excursie = v_cod_excursie;

    v_orase.EXTEND;
    v_orase(v_orase.last) := 'Maramures';
    
    UPDATE excursie_ane
    SET orase = v_orase
    WHERE cod_excursie = v_cod_excursie;
END;
/