Variant 1
=========

- Pool keeps list of free IDs
- Handle calls back to pool on destruction and frees ID
- New resource is created if needed

TODO:
- How to create a resource with non-default ctor?
- Multi-Pool (one object to store multiple resource types)?
