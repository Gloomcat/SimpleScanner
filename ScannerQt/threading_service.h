#pragma once

#ifndef THREADING_SERVICE_H
#define THREADING_SERVICE_H

#include "thread_pool.h"

namespace SimpleScanner {

	// Class for TPool jobs and resources management
	template <class ResultType>
	class TService {

	public:
		
		typedef std::function<void(ResultType)> result_callback;
		typedef const uint32_t&& threads_count;

		// Forwards tasks to TPool
		template <typename Job, typename... Args>
		void enqueue_job(Job&& func, Args&&... args) {

			t_pool->enqueue(std::forward<Job>(func), std::forward<Args>(args)...);

		}

		// Defaults to max value between 2 threads and 2 threads per CPU core
        TService(result_callback&& r_callback = std::move([](ResultType){}), threads_count&& num_threads =
			std::move(std::max(std::thread::hardware_concurrency() * 2, 2u))) {

			t_pool = std::make_unique<TPool<ResultType>>(
				std::forward<result_callback>(r_callback),
				std::forward<threads_count>(num_threads));

		}

		// Resets TPool and stop all curent works
		void reset() {
			t_pool->reset();
		}

		~TService() = default;

	private:

		// Unique TPool instance
		std::unique_ptr<TPool<ResultType>> t_pool;

	};
}

#endif
