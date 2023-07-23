SELECT rating,title FROM movies, ratings WHERE movies.id IN
    (SELECT id FROM movies WHERE year = 2010) AND movies.id = ratings.movie_id ORDER BY rating DESC, title ASC;