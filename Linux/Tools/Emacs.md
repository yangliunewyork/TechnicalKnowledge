Emacs /ˈiːmæks/ is a family of text editors that are characterized by their extensibility. The manual for the most widely used variant, GNU Emacs, describes it as "the extensible, customizable, self-documenting, real-time display editor".Development of the first Emacs began in the mid-1970s, and work on its direct descendent, GNU Emacs, continues actively as of 2017.

Emacs has over 10,000 built-in commands and its user interface allows the user to combine these commands into macros to automate work. Additionally, implementations of Emacs typically feature a dialect of the Lisp programming language that provides a deep extension capability, allowing users and developers to write new commands and applications for the editor.

### The Emacs Initialization File

When Emacs is started, it normally tries to load a Lisp program from an initialization file, or init file for short. This file, if it exists, specifies how to initialize Emacs for you. Emacs looks for your init file using the filenames ~/.emacs, ~/.emacs.el, or ~/.emacs.d/init.el; you can choose to use any one of these three names (see Find Init). Here, ~/ stands for your home directory.

