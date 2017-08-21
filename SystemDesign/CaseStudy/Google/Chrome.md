* http://dev.chromium.org/developers/design-documents/multi-process-architecture

This document describes Chromium's high-level architecture.

# Problem

It's nearly impossible to build a rendering engine that never crashes or hangs. It's also nearly impossible to build a rendering engine that is perfectly secure.

In some ways, the state of web browsers around 2006 was like that of the single-user, co-operatively multi-tasked operating systems of the past. As a misbehaving application in such an operating system could take down the entire system, so could a misbehaving web page in a web browser. All it took is one browser or plug-in bug to bring down the entire browser and all of the currently running tabs.

Modern operating systems are more robust because they put applications into separate processes that are walled off from one another. A crash in one application generally does not impair other applications or the integrity of the operating system, and each user's access to other users' data is restricted.

# Architectural overview

![alt](https://a77db9aa-a-7b23c8ea-s-sites.googlegroups.com/a/chromium.org/dev/developers/design-documents/multi-process-architecture/arch.png)

We use separate processes for browser tabs to protect the overall application from bugs and glitches in the rendering engine. We also restrict access from each rendering engine process to others and to the rest of the system. In some ways, this brings to web browsing the benefits that memory protection and access control brought to operating systems.

We refer to the main process that runs the UI and manages tab and plugin processes as the "browser process" or "browser." Likewise, the tab-specific processes are called "render processes" or "renderers." The renderers use the Blink open-source layout engine for interpreting and laying out HTML.

##### Why does Google chrome create multiple processes for multiple tabs?

If either one of these processes crashes (except the browser UI), it will just crash that, and not the entire browser. Before Chrome, all it took is one browser or plug-in/extension bug to bring down the entire browser process. Instead of doing just that, each process is living on its own. And that required a different architectural design, that is why in Chrome, once something crashes, only that processes crash and shows the Sad Face tab or plugin.
 
Multi-process architecture allows for a lot of flexibility in the way Chromium does security. The entire HTML rendering and JavaScript execution is isolated to its own class of processes; the renderers. These are the ones that live in the sandbox.
