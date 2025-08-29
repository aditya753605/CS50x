-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1: Confirm the crime scene details (date and street)
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2024 AND street = 'Humphrey Street';

-- Step 2: Find people exiting the bakery between 10:15 and 10:25 on the day of the crime
SELECT name
FROM people
JOIN bakery_security_logs
  ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2024
  AND hour = 10
  AND minute >= 15 AND minute < 25
  AND activity = 'exit';

-- Step 3: Identify who withdrew cash at the Leggett Street ATM earlier that day
SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28 AND month = 7 AND year = 2024
  AND transaction_type = 'withdraw'
  AND atm_location = 'Leggett Street';

-- Step 4: Find who made a phone call under 60 seconds on the morning of the theft
SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE day = 28 AND month = 7 AND year = 2024
  AND duration < 60;

-- Step 5: Who took the earliest flight out of town the next day?
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = (
    SELECT id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2024
    ORDER BY hour, minute
    LIMIT 1
);

-- Step 6: Combine conditions to isolate the thief
SELECT name
FROM people
WHERE name IN (
    SELECT name
    FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    WHERE passengers.flight_id = (
        SELECT id
        FROM flights
        WHERE day = 29 AND month = 7 AND year = 2024
        ORDER BY hour, minute
        LIMIT 1
    )
)
AND name IN (
    SELECT name
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE day = 28 AND month = 7 AND year = 2024
      AND transaction_type = 'withdraw'
      AND atm_location = 'Leggett Street'
)
AND name IN (
    SELECT name
    FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE day = 28 AND month = 7 AND year = 2024
      AND duration < 60
)
AND name IN (
    SELECT name
    FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE day = 28 AND month = 7 AND year = 2024
      AND hour = 10
      AND minute >= 15 AND minute < 25
      AND activity = 'exit'
);

-- Step 7: Find the destination city of that flight
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2024
    ORDER BY hour, minute
    LIMIT 1
);

-- Step 8: Identify the accomplice (the person called by the thief in < 60-second call)
SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE day = 28 AND month = 7 AND year = 2024
  AND duration < 60
  AND caller = (
      SELECT phone_number
      FROM people
      WHERE name = 'Bruce'
  );
