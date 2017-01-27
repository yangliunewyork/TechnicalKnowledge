## I/O Devices
I/O devices generally consist of two parts: a controller and the device itself. The controller is a chip or a set of chips on a plug-in board that physically controls the device. It accepts commands from the operating system, for example, to read data from the device, and carries them out.

In many cases, the actual control of the device is very complicated and detailed, so it is the job of the controller to present a simpler interface to the operating system. For example, a disk controller might accept a command to read sector 11,206 from disk 2. The controller then has to convert this linear sector number to a cylinder, sector, and head. This conversion may be complicated by the fact that outer cylinders have more sectors than inner ones and that some bad sectors have been remapped onto other ones. Then the controller has to determine which cylinder the disk arm is on and give it a sequence of pulses to move in or out the requisite number of cylinders. It has to wait until the proper sector has rotated under the head and then start reading and storing the bits as they come off the drive, removing the preamble and computing the checksum. Finally, it has to assemble the incoming bits into words and store them in memory. To do all this work, controllers often contain small embedded computers that are programmed to do their work.

The other piece is the actual device itself. Devices have fairly simple interfaces, both because they cannot do much and to make them standard. The latter is needed so that any IDE disk controller can handle any IDE disk, for example. IDE stands for Integrated Drive Electronics and is the standard type of disk on Pentiums and some other computers. Since the actual device interface is hidden behind the controller, all that the operating system sees is the interface to the controller which may be quite different from the interface to the device.

Because each type of controller is different, different software is needed to control each one. The software that talks to a controller, giving it commands and accepting responses, is called a __device driver__.

To be used, the driver has to be put into the operating system so it can run in kernel mode. Theoretically, drivers can run outside the kernel, but few current systems support this possibility because it requires the ability to allow a user-space driver to be able to access the device in a controlled way, a feature rarely supported.

## How input/output is handled

Input and output can be done in three different ways. In the simplest method, a user program issues a system call, which the kernel then translates into a procedure call to the appropriate driver. The driver then starts the I/O and sits in a tight loop continuously polling the device to see if it is done (usually there is some bit that indicates that the device is still busy). When the I/O has completed, the driver puts the data where they are needed (if any), and returns. The operating system then returns control to the caller. This method is called __busy waiting__ and has the disadvantage of tying up the CPU polling the device until it is finished.

The second method is for the driver to start the device and ask it to give an interrupt when it is finished. At that point the driver returns. The operating system then blocks the caller if need be and looks for other work to do. When the controller detects the end of the transfer, it generates an __interrupt__ to signal completion.

The third method for doing I/O makes use of a special DMA (Direct Memory Access) chip that can control the flow of bits between memory and some controller without constant CPU intervention. The CPU sets up the DMA chip telling it how many bytes to transfer, the device and memory addresses involved, and the direction, and lets it go. When the DMA chip is done, it causes an interrupt.

### What are the advantages of direct memory access over interrupt-driven I/O?

DMA saves lots of CPU time so that CPU can have more time to execute CPU-bound tasks. 

In a simple computer architecture, CPU and  IO devices are linked with a bus. if CPU wants to get data from IO device, it will send a message to IO device via bus and wait for its response. During this time, CPU can do nothing except waiting for data. This method seems to waste CPU resource a lot and one solution of this problem is DMA.

In a computer architecture with DMA, CPU, DMA and memory are linked with a bus. And DMA will have an exclusive IO bus connected with IO devices. In order to get data from IO device, CPU just need to send a message to DMA and do any other task instead of waiting. After DMA receives the message, it first fetchs data from IO device and then put data in memory. Finally, it sends an interrupt to CPU for telling him the IO operation is finished, and CPU gets that IO data from memory after receiving the interrupt.

Writing data to IO device is similar to reading, and DMA can reduce the CPU waiting time of both IO operations.


