SELECT title FROM movies,ratings WHERE movies.id IN
    (SELECT movie_id FROM ratings WHERE movie_id IN
        (SELECT movie_id FROM stars WHERE person_id =
            (SELECT id FROM people WHERE name = 'Chadwick Boseman'))) and ratings.movie_id = movies.id ORDER BY rating DESC LIMIT 5;