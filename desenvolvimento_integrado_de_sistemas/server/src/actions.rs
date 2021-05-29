use diesel::prelude::*;

use crate::models::{self, Signal};

/// Run query using Diesel to find user by uid and return it.
pub fn find_all_requests(
    conn: &SqliteConnection,
) -> Result<Option<Vec<models::Signal>>, diesel::result::Error> {
    use crate::schema::signals::dsl::*;

    let user = signals.load::<models::Signal>(conn).optional().unwrap();

    Ok(user)
}

/// Run query using Diesel to insert a new database row and return the result.
pub fn insert_new_signal(
    model: models::Signal,
    // prevent collision with `name` column imported inside the function
    conn: &SqliteConnection,
) -> Result<models::Signal, diesel::result::Error> {
    // It is common when using Diesel with Actix web to import schema-related
    // modules inside a function's scope (rather than the normal module's scope)
    // to prevent import collisions and namespace pollution.
    use crate::schema::signals::dsl::*;

    diesel::insert_into(signals).values(&model).execute(conn)?;

    Ok(model)
}

pub fn update_signal(
    model: models::Signal,
    // prevent collision with `name` column imported inside the function
    conn: &SqliteConnection,
) -> Result<models::Signal, diesel::result::Error> {
    // It is common when using Diesel with Actix web to import schema-related
    // modules inside a function's scope (rather than the normal module's scope)
    // to prevent import collisions and namespace pollution.
    use crate::schema::signals::dsl::*;

    diesel::update(signals.filter(token.eq(&model.token)))
        .set(status.eq(&model.status))
        .execute(conn)?;

    Ok(model)
}

pub fn insert_new_image(
    model: models::Image,
    // prevent collision with `name` column imported inside the function
    conn: &SqliteConnection,
) -> Result<models::Image, diesel::result::Error> {
    // It is common when using Diesel with Actix web to import schema-related
    // modules inside a function's scope (rather than the normal module's scope)
    // to prevent import collisions and namespace pollution.
    use crate::schema::images::dsl::*;

    diesel::insert_into(images).values(&model).execute(conn)?;

    Ok(model)
}

pub fn find_image(
    model: models::Signal,
    conn: &SqliteConnection,
) -> Result<Option<models::Image>, diesel::result::Error> {
    use crate::schema::images::dsl::*;

    let image = images
        .filter(token.eq(model.token.to_string()))
        .first::<models::Image>(conn)
        .optional()?;

    Ok(image)
}

pub fn find_signal(
    model: models::Signal,
    conn: &SqliteConnection,
) -> Result<Option<models::Signal>, diesel::result::Error> {
    use crate::schema::signals::dsl::*;

    let signal = signals
        .filter(token.eq(model.token.to_string()))
        .first::<models::Signal>(conn)
        .optional()?;

    Ok(signal)
}
