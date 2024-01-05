/*
BStone: Unofficial source port of Blake Stone: Aliens of Gold and Blake Stone: Planet Strike
Copyright (c) 2023-2024 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors
SPDX-License-Identifier: MIT
*/

// Thread-safe, arena memory resource with auto-reseting size.

#if !defined(BSTONE_TS_AUTO_ARENA_MEMORY_RESOURCE_INCLUDED)
#define BSTONE_TS_AUTO_ARENA_MEMORY_RESOURCE_INCLUDED

#include <mutex>

#include "bstone_cxx.h"
#include "bstone_auto_arena_memory_resource.h"

namespace bstone {

class TsAutoArenaMemoryResource : public MemoryResource
{
public:
	TsAutoArenaMemoryResource() noexcept = default;
	TsAutoArenaMemoryResource(std::intptr_t capacity, MemoryResource& memory_resource);
	~TsAutoArenaMemoryResource() override = default;

	std::intptr_t get_capacity() noexcept;
	std::intptr_t get_size() noexcept;

	void reserve(std::intptr_t capacity, MemoryResource& memory_resource);

private:
	BSTONE_CXX_NODISCARD void* do_allocate(std::intptr_t size) override;
	void do_deallocate(void* ptr) noexcept override;

private:
	using Mutex = std::mutex;
	using MutexLock = std::unique_lock<Mutex>;

private:
	Mutex mutex_{};
	AutoArenaMemoryResource arena_{};
};

} // namespace bstone

#endif // BSTONE_TS_AUTO_ARENA_MEMORY_RESOURCE_INCLUDED
