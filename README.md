# template

Template manager for unix systems.

## Usage

`template new_name template_name` searches the templates directory for
`template_name` and, after the uses chooses an option (or optionally searches
again with a different term), the template is copied into the working directory
and renamed to `new_name`.

- The `-extension` (`-e`) flag can be used to filter search results by those
with the same extension as the search query, including none.
- The `-dir` (`-d`) flag can be used to override the default template directory
and search the given argument instead.
