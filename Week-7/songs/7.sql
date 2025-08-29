SELECT AVG(energy) FROM songs
where artist_id =
(
    SELECt id
    FROM artists
    where name = 'Drake'
);
