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

/*
SELECT *
FROM excursie_ane;
/
SELECT cod_excursie,t.*
FROM excursie_ane e, TABLE(e.orase) t
/
UPDATE TABLE(SELECT orase from excursie_ane WHERE cod_excursie = 1)
SET COLUMN_VALUE = 'Busteni'
WHERE COLUMN_VALUE = 'Azuga';
/
DEFINE p_cod = 1
DECLARE
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
BEGIN
    SELECT orase 
    INTO v_orase
    FROM excursie_ane
    WHERE cod_excursie = v_cod_excursie;
END;
*/

-- a
INSERT INTO excursie_ane VALUES (1,'interna',tip_orase_ane('Ploiesti','Azuga','Brasov'), 'disponibila');
INSERT INTO excursie_ane VALUES (2,'munte', tip_orase_ane('Sinaia','Brasov','Azuga'), 'disponibila');
INSERT INTO excursie_ane VALUES (3,'mare', tip_orase_ane('Mamaia','Costinesti','Eforie Nord'), 'indisponibila');
INSERT INTO excursie_ane VALUES (4,'strainatate',tip_orase_ane('Budapesta','Belgrad','Madrid'), 'indisponibila');
INSERT INTO excursie_ane VALUES (5,'asia',tip_orase_ane('China','Japonia'), 'disponibila');

-- b
DEFINE p_cod = 1
DEFINE p_oras_1 = 'Ploiesti'
DEFINE p_oras_2 = 'Azuga'
DEFINE p_oras_eliminare = 'Brasov'
DECLARE
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
    index_eliminare NUMBER;
BEGIN
    SELECT orase 
    INTO v_orase
    FROM excursie_ane
    WHERE cod_excursie = v_cod_excursie;

    -- Adaugarea unui oras nou in lista (ultimul vizitat)
    v_orase.EXTEND;
    v_orase(v_orase.last) := 'Maramures';
    
    -- Adaugarea unui oras nou in lista (al doilea vizitat)
    v_orase.EXTEND;
    FOR i IN REVERSE 3..v_orase.last LOOP
        v_orase(i) := v_orase(i - 1);
    END LOOP;
    v_orase(2) := 'Suceava';
    
    -- Inversarea ordinii a doua orase
    FOR i IN v_orase.first..v_orase.last LOOP
        IF v_orase(i) = '&p_oras_1' THEN
            v_orase(i) := '&p_oras_2';
        ELSIF v_orase(i) = '&p_oras_2' THEN
            v_orase(i) := '&p_oras_1';
        END IF;
    END LOOP;
    
    -- Eliminarea orasului
    FOR i IN v_orase.first..v_orase.last LOOP
        IF v_orase(i) = '&p_oras_eliminare' THEN
            index_eliminare := i;
        END IF;
    END LOOP;
    v_orase.DELETE(index_eliminare);
            
    UPDATE excursie_ane
    SET orase = v_orase
    WHERE cod_excursie = v_cod_excursie;
END;
/
ROLLBACK;

-- c
DECLARE
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
BEGIN
    SELECT orase 
    INTO v_orase
    FROM excursie_ane
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Numar orase vizitate: '||v_orase.COUNT);

    FOR i IN v_orase.first..v_orase.last LOOP
        DBMS_OUTPUT.PUT_LINE(v_orase(i));
    END LOOP;
END;
/

-- d
DECLARE
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
    v_cod_maxim_excursie excursie_ane.cod_excursie%TYPE;
    v_nume_excursie excursie_ane.denumire%TYPE;
BEGIN
    SELECT MAX(cod_excursie)
    INTO v_cod_maxim_excursie
    FROM excursie_ane;
    
    FOR i IN 1..v_cod_maxim_excursie LOOP
        SELECT denumire
        INTO v_nume_excursie
        FROM excursie_ane
        WHERE cod_excursie = i;
        
        DBMS_OUTPUT.PUT_LINE(chr(10)||'Excursia '||v_nume_excursie);
        
        SELECT orase 
        INTO v_orase
        FROM excursie_ane
        WHERE cod_excursie = i;
        
        FOR j IN v_orase.first..v_orase.last LOOP
            DBMS_OUTPUT.PUT_LINE(v_orase(j));
        END LOOP;
    END LOOP;
END;
/

-- e
DECLARE
    TYPE vector IS VARRAY(64) OF NUMBER;
    v_nr_orase vector := vector();
    v_orase excursie_ane.orase%TYPE;
    v_cod_excursie excursie_ane.cod_excursie%TYPE := &p_cod;
    v_cod_maxim_excursie excursie_ane.cod_excursie%TYPE;
    v_orase_minim excursie_ane.denumire%TYPE := -1;
BEGIN
    SELECT MAX(cod_excursie)
    INTO v_cod_maxim_excursie
    FROM excursie_ane;
    
    FOR i IN 1..v_cod_maxim_excursie LOOP
        SELECT orase 
        INTO v_orase
        FROM excursie_ane
        WHERE cod_excursie = i;
       
        v_nr_orase.EXTEND;
        v_nr_orase(i) := v_orase.COUNT;
        IF v_orase_minim = -1 OR v_nr_orase(i) < v_orase_minim THEN
            v_orase_minim := v_nr_orase(i);
        END IF;
    END LOOP;
    FOR i IN v_nr_orase.first..v_nr_orase.last LOOP
        IF v_nr_orase(i) = v_orase_minim THEN
            DELETE FROM excursie_ane
            WHERE cod_excursie = i;
        END IF;
    END LOOP;
END;
/
ROLLBACK;