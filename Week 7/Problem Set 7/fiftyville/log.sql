-- Keep a log of any SQL queries you execute as you solve the mystery.

-- find crime scene description
SELECT id,description FROM crime_scene_reports WHERE
    street = 'Humphrey Street' AND
    day = 28 AND
    year = 2021 AND
    month = 7;

-- id 295
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.

-- id 297
-- Littering took place at 16:36. No known witnesses.

-- get witnesses licence plate of exits around the time of the crime
SELECT * FROM bakery_security_logs WHERE
    activity = 'exit' AND
    day = 28 AND
    year = 2021 AND
    month = 7 AND
    hour = 10;

-- get transcript of interviews and names
SELECT id, name, transcript FROM interviews WHERE
    day = 28 AND
    year = 2021 AND
    month = 7;

-- | 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- info about phone calls
SELECT * from phone_calls WHERE
    day = 28 AND
    year = 2021 AND
    month = 7 AND
    duration < 60;

-- info about atm
SELECT account_number, transaction_type, amount FROM atm_transactions WHERE
    day = 28 AND
    year = 2021 AND
    month = 7 AND
    atm_location = 'Leggett Street';


-- people that used the atm on Leggett Street on the day
SELECT * from people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'));


-- cross refrence people that used the atm on Leggett Street with witnesses licence plate of exits around the time of the crime

SELECT * from people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'))
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE
        activity = 'exit' AND
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        hour = 10 AND
        minute < 36);

-- crooss reference with the phone number
SELECT * from people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'))
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE
        activity = 'exit' AND
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        hour = 10)
    AND phone_number IN
    (SELECT caller from phone_calls WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        duration < 60);


-- the person that the theif called
SELECT receiver from people,phone_calls WHERE people.id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'))
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE
        activity = 'exit' AND
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        hour = 10)
    AND phone_number IN
    (SELECT caller from phone_calls WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        duration < 60)
    AND people.phone_number = phone_calls.caller
    AND phone_calls.day = 28 AND
        phone_calls.year = 2021 AND
        phone_calls.month = 7 AND
        phone_calls.duration < 60
    AND people.name = 'Bruce';





-- select earlyest flyght from fiftyville airport
SELECT * FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id IN
        (SELECT id FROM flights WHERE origin_airport_id =
            (SELECT id FROM airports WHERE city = 'Fiftyville') AND
            day = 29 AND
            year = 2021 AND
            month = 7 AND
            hour = 8));


SELECT * FROM people where passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id IN
        (SELECT id FROM flights WHERE origin_airport_id =
            (SELECT id FROM airports WHERE city = 'Fiftyville') AND
            day = 29 AND
            year = 2021 AND
            month = 7))
    AND name IN
        (SELECT name from people,phone_calls WHERE people.id IN
            (SELECT person_id FROM bank_accounts WHERE account_number IN
                (SELECT account_number FROM atm_transactions WHERE
                day = 28 AND
                year = 2021 AND
                month = 7 AND
                atm_location = 'Leggett Street'))
            AND license_plate IN
            (SELECT license_plate FROM bakery_security_logs WHERE
                activity = 'exit' AND
                day = 28 AND
                year = 2021 AND
                month = 7 AND
                hour = 10)
            AND phone_number IN
            (SELECT caller from phone_calls WHERE
                day = 28 AND
                year = 2021 AND
                month = 7 AND
                duration < 100)
            AND people.phone_number = phone_calls.caller
            AND phone_calls.day = 28 AND
                phone_calls.year = 2021 AND
                phone_calls.month = 7 AND
                phone_calls.duration < 100);




-- main suspects Bruce (he leaves first)
SELECT * from people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'))
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE
        activity = 'exit' AND
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        hour = 10)
    AND phone_number IN
    (SELECT caller from phone_calls WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        duration < 60)
INTERSECT
SELECT * FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id IN
        (SELECT id FROM flights WHERE origin_airport_id =
            (SELECT id FROM airports WHERE city = 'Fiftyville') AND
            day = 29 AND
            year = 2021 AND
            month = 7 AND
            hour = 8));

--name of city of escape
SELECT city FROM airports WHERE id IN
    (SELECT destination_airport_id FROM flights WHERE origin_airport_id =
            (SELECT id FROM airports WHERE city = 'Fiftyville') AND
            day = 29 AND
            year = 2021 AND
            month = 7 AND
            hour = 8);

--name of acomplice
SELECT name FROM people WHERE phone_number IN
    (SELECT receiver from people,phone_calls WHERE people.id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        atm_location = 'Leggett Street'))
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE
        activity = 'exit' AND
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        hour = 10)
    AND phone_number IN
    (SELECT caller from phone_calls WHERE
        day = 28 AND
        year = 2021 AND
        month = 7 AND
        duration < 60)
    AND people.phone_number = phone_calls.caller
    AND phone_calls.day = 28 AND
        phone_calls.year = 2021 AND
        phone_calls.month = 7 AND
        phone_calls.duration < 60
    AND people.name = 'Bruce');