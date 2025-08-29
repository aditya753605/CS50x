SELECT AVG(rating)
FROM ratings
where movie_id IN
(SELECT id from movies where year = 2012);
