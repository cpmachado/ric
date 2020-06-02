# model

The application owns two disjoint parts: The Application, and The Library.

## The Application

The Application should implement:
- The CLI:
	+ It receives and multiplexes arguments to any given task.

## Library

The Library should implement:
- The Library:
	+ It should solve the monolithic nature of each task, enabling the
	application to multiplex between each functionality.
	+ Extend the actions between each interacting parts, such as any I/O
	  present.

