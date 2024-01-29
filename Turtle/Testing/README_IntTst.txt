-----------------------------------------------------INTERPRETER----------------------------------------------------------------------------
Run with:
make combined
For Print to Screen:
make runcomb (uncommenting your TTL file)
For Print to txt:
make runcomb_txt (uncommenting your TTL)

Project Reflection:

    Testing to maximum from the start.
    Interpreting hardest part, understanding stack linked functionality in nested loops challenging.
    Should have emphasized rigorous testing earlier.

Testing Strategy:

    Used mintest.sh library, researched from separate source.
    Aimed for clarity with unit testing (blackbox approach).
    For whitebox, involved uncommenting each TTL file.

Bugs to Note:

    Bug1: Postfix implemented but ran out of time for full function integration. See commented section in interp.c.
    Bug2: Issues with .sh files, especially nested loops leading to segmentation faults. Required extensive test adjustments. Project continuously evolving.
    Bug3: Occasional (null) output in write-to-txt function.
    Bug4: Nested loop color setting issue; prints same color, though differences visible on screen.

Reflections on Process:

    Started with promising ideas.
    Panic led to hasty changes in function and tests.
    Quick fixes found when asking for help – more efficient than days of struggle.
    Illness impacted final days; lesson in contingency planning.
    Valuable learning experience in programming this term.