SELECT title
FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
WHERE movies.id IN (

    SELECT movie_id
    FROM ratings
    WHERE movie_id IN (

        SELECT movie_id
        FROM stars
        WHERE person_id = (

            SELECT id
            FROM people
            WHERE name = 'Chadwick Boseman'
        )
    )
)
ORDER BY ratings.rating DESC LIMIT 5;
