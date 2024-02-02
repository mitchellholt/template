# template

Template manager for linux systems.

## Usage

```
template <cmd> <args...>
```
The valid commands are
- `ls`. List all template files (if any).
- `from`. Create a new file from an existing template. The first argument must be the name of an
  existing template. The second (optional) argument is the name to be given to a copy of the file in
  the working directory.
- `new`. Create a new template file. The first argument must be the name of the existing file to use as
  a new template. The second (optional) argument is the name to be given to the new template.
- `write`. Overwrite an existing template file with the contents of an existing file. The first argument
  must be the name of the template, and the second the name of the existing file.

The template directory is stored in the `TEMPLATE_DIRECTORY` environment variable. If this is not set,
then the default location`~/Documents/Templates/` will be used.

## Installation

Clone this repository somewhere locally and run `make` to produce an executable.
