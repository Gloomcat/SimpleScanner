#pragma once

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <type_traits>
#include <vector>
#include <future>
#include <iostream>

#include "threading_components.h"


namespace SimpleScanner {


	template <class ResultType>
	class TPool {

	public:

		typedef std::future<ResultType> unique_result;
		typedef std::unique_ptr<ITask> unique_task_ptr;
		typedef std::function<void(ResultType)> result_callback;
		typedef const uint32_t&& threads_count;

		// Enqueue a job to be run by a thread pool.
		template <typename Job, typename... Args>
		void enqueue(Job&& job, Args&&... args) {

			auto bound_task = std::bind(std::forward<Job>(job), std::forward<Args>(args)...);

			using PackagedTask = std::packaged_task<ResultType()>;
			using TaskType = Task<PackagedTask>;

			PackagedTask task(std::move(bound_task));
			
			results_queue.push_obj(task.get_future());
			task_queue.push_obj(std::make_unique<TaskType>(std::move(task)));
		}

		explicit TPool(result_callback r_callback, threads_count num_threads)
			: r_callback(r_callback), pool_done(false) {

			try	{

				//workers.emplace_back(&TPool::aggregate_results, this);

				for (uint32_t i = 0u; i < num_threads; i++) {

					workers.emplace_back(&TPool::work, this);
				}

			} catch (...) {

				destroy();
				throw;

			}

		}

        // Clear pending tasks and results
		void reset() {

			active_future_task_results.invalidate_queue();
			results_queue.invalidate_queue();
			task_queue.invalidate_queue();

			//TODO: handle thread locking in some conditions

			active_future_task_results.validate_queue();
			results_queue.validate_queue();
			task_queue.validate_queue();

		}

		TPool(const TPool& rhs) = delete;
		TPool& operator=(const TPool& rhs) = delete;

		~TPool(void) {

			destroy();

		}

	private:

		// Default routine for each worker
		void work() {

			while (!pool_done) {

				unique_task_ptr pTask(nullptr);
				unique_result res;

				if (task_queue.pop_obj(pTask))	{
					if (results_queue.pop_obj(res) && res.valid()) {
						active_future_task_results.push_obj(std::move(res));
					}
					pTask->do_job();
				}

				if (active_future_task_results.pop_obj(res) && res.valid()) {
					r_callback(res.get());
				}

			}
		}

		// Perform safe stop on pool components
		void destroy() {

			pool_done = true;

			active_future_task_results.invalidate_queue();
			results_queue.invalidate_queue();
			
			task_queue.invalidate_queue();

			for (auto& worker : workers) {

				if (worker.joinable()) {

					worker.join();

				}
			}
		}

		std::atomic<bool> pool_done;
		
		TSQueue<unique_result> results_queue;
		TSQueue<unique_result> active_future_task_results;
		TSQueue<unique_task_ptr> task_queue;
		
		std::vector<std::thread> workers;

		// Callback for special result processing
		result_callback r_callback;
		
	};

}

#endif
