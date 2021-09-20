---
layout: post
title:  "Where are D3D12 Descriptor heaps allocated?"
excerpt: "Sysmem or Vidmem?"
date:   2021-09-18 01:00:00
---


D3D12 introduces the concepts of Descriptors and Descriptor Heaps. A descriptor is nothing but a small amount of data describing where a specific resource is resident along with its parameters. Think of it as a "view" of a resource. The exact format of a descriptor is GPU specific. The only thing to note about the format is that the descriptor would contain a pointer to the actual resource as shown below:

![](https://software.intel.com/content/dam/develop/external/us/en/images/descriptor-that-represents-a-view-545120.png)

Now, the only way of interacting with descriptors in D3D12 is via Descriptor Heaps. Descriptor Heaps are an array of descriptors and during creation of these heaps, the types of descriptors that are being stored in the heap is specified. Currently, four types of Descriptor heaps are supported:

1. CBV / SRV / UAV Heaps.
2. Sampler heaps.
3. Render target view heaps.
4. Depth Stencil heaps.

One important question to ask here is where exactly is the descriptor heap allocated? Is it sysmem or vidmem? For one, in the Build 2014 conference where a preview of D3D12 was shown, it was explicitly stated that descriptor heaps are stored in vidmem as shown below:

![]({{ site.url }}/assets/d3d12_build2014_descTable.png)

But this isn't entirely accurate since the RTV and DSV heaps are not required to be allocated in vidmem. These are allocated in sysmem.

This is because the GPU does not read from the resources pointed to by the RTV or the DSV descriptors. Only those descriptors that point to resources that the GPU reads from need to be allocated in vidmem/shader visible since the GPU would access the descriptors to gain access to the actual resource resident in vidmem. Whereas with an RTV, it's the ICD that does a read on the descriptor to get the VA of the actual render target buffer resident(hopefully) in vidmem.

When ``ID3D12GraphicsCommandList::OMSetRenderTargets`` is present in the commad queue, the ICD would translate this into a GPU method that would set the current active render target to the one pointed to by the VA in the descriptor. Since all this is done on the CPU, RTVs are not shader visible and the allocation for these descriptor heaps comes from sysmem.
