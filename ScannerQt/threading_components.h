#pragma once

#ifndef THREADING_COMPONENTS_H
#define THREADING_COMPONENTS_H

#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace SimpleScanner {
	

	class ITask
	{
	public:
		ITask() = default;
		virtual ~ITask() = default;
		ITask(const ITask& rhs) = delete;
		ITask& operator=(const ITask& rhs) = delete;

		// Execute task's job
		virtual void do_job() = 0;
	};


	// Task implementation 
	template <class T>
	class Task : public ITask {

	public:
		Task(T&& job) : t_job(std::move(job)) {}

		~Task() override = default;
		Task(const Task& rhs) = delete;
		Task& operator=(const Task& rhs) = delete;

		// Execute task's job
		void do_job() override {

			t_job();

		}

	private:

		T t_job;

	};

	// Templated thread safe queue
	template<class T>
	class TSQueue {

	public:

		typedef std::lock_guard<std::mutex> g_Lock;
		typedef std::unique_lock<std::mutex> u_Lock;

		// Blocking retrieve of obj from queue
		bool pop_obj(T& out) {

			u_Lock lock(q_access);

			q_condvar.wait(lock, [this]() {
				return !ts_queue.empty() || !q_valid;
			});

			if (!q_valid)
				return false;

			out = std::move(ts_queue.front());
			ts_queue.pop();

			return true;

		}

		// Add obj to queue
		void push_obj(T in) {

			g_Lock lock(q_access);

			ts_queue.push(std::move(in));
			q_condvar.notify_one();

		}

		// Set validity
		void validate_queue() {

			g_Lock lock(q_access);

			q_valid = true;
			q_condvar.notify_all();
		
		}

		// Invalidate and empty queue;
		void invalidate_queue() {

			g_Lock lock(q_access);

			q_valid = false;
			q_condvar.notify_all();

			while (!ts_queue.empty()) {

				ts_queue.pop();

			}

		}

		// Setup validity
		TSQueue() : q_valid(true) {}

		// Invalidate and empty queue;
		~TSQueue() {

			invalidate_queue();

		}

	private:

		std::atomic<bool> q_valid;
		std::condition_variable q_condvar;
		std::mutex q_access;
		std::queue<T> ts_queue;
	};

}

#endif
