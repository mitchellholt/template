# template

Template manager for unix systems.

## Usage

`template new_name template_name [template_directory_path]` searches the
templates directory for `template_name` and, after the uses chooses an option
(or optionally searches again with a different term), the template is copied
into the working directory and renamed to `new_name`.

If the `template_directory_path` argument is not supplied, the
`TEMPLATE_DIRECTORY` environment variable is searched, then the default location
`~/Documents/Templates/` will be used.

The `-extension` (`-e`) flag can be used to filter search results by those
with the same extension as the search query, including none.
