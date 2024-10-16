CREATE TABLE OCTOMBRIE_ANE(id NUMBER, data DATE);

DECLARE
    contor NUMBER(6) := 0;
    v_data DATE := TO_DATE('01-OCT-2023', 'DD-MON-YYYY');
BEGIN
    LOOP
        v_data := TO_DATE('01-OCT-2023', 'DD-MON-YYYY') + contor;
        contor := contor + 1;
        INSERT INTO OCTOMBRIE_ANE
        VALUES (contor, v_data);
        EXIT WHEN v_data = TO_DATE('31-OCT-2023', 'DD-MON-YYYY');
    END LOOP;
END;
/

SELECT *
FROM OCTOMBRIE_ANE;

DECLARE 
v_cod_dep employees.department_id%TYPE:=&p_cod_dep;
v_cod_ang employees.employee_id%TYPE;
BEGIN
SELECT employee_id
INTO v_cod_ang
FROM employees
WHERE department_id = v_cod_dep;
DBMS_OUTPUT.PUT_LINE('In dep cu codul '|| v_cod_dep|| ' lucreaza ang cu codul '|| v_cod_ang);
EXCEPTION
WHEN TOO_MANY_ROWS THEN
    RAISE_APPLICATION_ERROR(-20001, 'Prea multe date!');
WHEN NO_DATA_FOUND THEN
    RAISE_APPLICATION_ERROR(-20000, 'Nu exista date!');
END;
/

SELECT *
FROM MEMBER;

DECLARE
v_nume member.last_name%TYPE:='&p_nume';
v_count NUMBER(6);
BEGIN
SELECT COUNT(copy_id)
INTO v_count
FROM rental
JOIN member USING(member_id)
WHERE UPPER(last_name) = UPPER(v_nume)
GROUP BY member_id;
CASE WHEN v_count = 1
          THEN DBMS_OUTPUT.PUT_LINE('Membrul '|| v_nume|| ' a imprumutat '|| v_count||' film');
     ELSE DBMS_OUTPUT.PUT_LINE('Membrul '|| v_nume|| ' a imprumutat '|| v_count||' filme');
END CASE;
EXCEPTION
WHEN TOO_MANY_ROWS THEN
    RAISE_APPLICATION_ERROR(-20001, 'Prea multe date!');
WHEN NO_DATA_FOUND THEN
    RAISE_APPLICATION_ERROR(-20000, 'Nu exista date!');
END;
/

-- E4
DECLARE
v_nume member.last_name%TYPE:='&p_nume';
v_count NUMBER(6);
v_total_count NUMBER(6);
v_categorie NUMBER(1);
BEGIN
SELECT COUNT(title_id)
INTO v_total_count
FROM title;
SELECT COUNT(copy_id)
INTO v_count
FROM rental
JOIN member USING(member_id)
WHERE UPPER(last_name) = UPPER(v_nume)
GROUP BY member_id;
CASE WHEN v_count > 75 * v_total_count / 100
          THEN v_categorie := 1;
     WHEN v_count > 50 * v_total_count / 100  
          THEN v_categorie := 2;
     WHEN v_count > 25 * v_total_count / 100
          THEN v_categorie := 3;
     ELSE v_categorie := 4;
END CASE;
DBMS_OUTPUT.PUT_LINE('Membrul '|| v_nume|| ' face parte din categoria '|| v_categorie);
END;
/


CREATE TABLE member_ane
AS SELECT * FROM member;

ALTER TABLE member_ane 
ADD discount NUMBER(6);

DECLARE
    v_cod_membru member.last_name%TYPE:='&p_cod';
    v_count NUMBER(6);
    v_total_count NUMBER(6);
    v_discount NUMBER(6);
    v_nr NUMBER(6);
BEGIN
    SELECT COUNT(*)
    INTO v_nr
    FROM member
    WHERE member_id = v_cod_membru;
    IF v_nr = 0 THEN
        RAISE_APPLICATION_ERROR(-20000, 'Nu exista date!');
        ELSE
        SELECT COUNT(title_id)
        INTO v_total_count
        FROM title;
        SELECT COUNT(copy_id)
        INTO v_count
        FROM rental r
        JOIN member m ON(r.member_id = m.member_id)
        WHERE r.member_id = v_cod_membru
        GROUP BY r.member_id;
        IF v_total_count = 0 THEN
            RAISE_APPLICATION_ERROR(-20001, 'Membrul nu a imprumutat nimic!');
            ELSE
            CASE WHEN v_count > 75 * v_total_count / 100
                      THEN v_discount := 10;
                 WHEN v_count > 50 * v_total_count / 100  
                      THEN v_discount := 5;
                 WHEN v_count > 25 * v_total_count / 100
                      THEN v_discount := 3;
                 ELSE v_discount := 0;
            END CASE;
        END IF;
        UPDATE member_ane
        SET discount = v_discount
        WHERE member_id = v_cod_membru;
    END IF;
END;
/

SELECT * FROM member_ane;

-- Scrieti un bloc PL/SQL in care stocati prin variabile de substitutie un cod al unui joc_video, un cod al unei categorii si procentul cu care se mareste durata acestuia. Sa se adauge jocul in noua categorie si sa i se creasca durata in mod corespunzator. Daca modificarea s-a putut realiza cu succes, sa se afiseze mesajul “Actualizare realizata”, iar in caz contrar mesajul “Nu exista un joc cu acest cod”. Anulati modificarile realizate.
DEFINE p_cod_joc = 1;
DEFINE p_cod_cat = 4;
DEFINE p_procent = 15;
DECLARE
    v_cod_joc joc_video.cod_joc%TYPE := &p_cod_joc;
    v_cod_cat categorie.cod_categorie%TYPE := &p_cod_cat;
    v_procent NUMBER(6) := &p_procent;
BEGIN
    INSERT INTO joc_video_categorie
    VALUES (v_cod_joc, v_cod_cat);
    UPDATE joc_video
    SET durata = durata + durata * v_procent / 100
    WHERE cod_joc = v_cod_joc;
    IF SQL % ROWCOUNT = 0
        THEN DBMS_OUTPUT.PUT_LINE('Nu exista joc cu acest id.');
    ELSE DBMS_OUTPUT.PUT_LINE('Actualizare realizata!');
    END IF;
END;
/
ROLLBACK;