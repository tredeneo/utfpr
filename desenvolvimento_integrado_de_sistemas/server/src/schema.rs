table! {
    signals (token) {
        token -> Text,
        algorithm -> Text,
        datetime -> Text,
        status -> Text,
    }
}

table! {
    images (token) {
        token -> Text,
        bytes -> Blob,
    }
}
