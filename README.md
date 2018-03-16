# envv
Replacement for coreutils-env with proper argument parsing

Good: `#!/usr/bin/make -f`
This works as expected

Bad: `#!/usr/bin/env make -f`
It gives error: /usr/bin/env: ‘make -f’: No such file or directory
This is because coreutils-env does not split the input on spaces.

We do! It's so simple. :-)

Usage:
```
#!/usr/bin/envv make -f
# rest of Makefile follows
```
