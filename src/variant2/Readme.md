Variant 2
=========

- Pool keeps a map of resources and weak_ptrs to handles
- On resource request checks all weak_ptrs if the handle was released (O(N) in number of resources...)
- New resource is created if needed

TODO:
- How to create a resource with non-default ctor?
- Multi-Pool (one object to store multiple resource types)?
