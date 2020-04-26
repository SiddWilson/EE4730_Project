#pragma once

#include <sstream>
#include <string>
#include <iomanip>
#include <mutex>
#include "Utilities.hpp"
#include "Defines.hpp"
#include "ConfigParser.hpp"

namespace Common
{
#define PROFILER_ON
	//#define PROFILE_STDOUT

#ifdef __GNUC__
	inline std::string methodName(const std::string& prettyFunction)
	{
		size_t colons = prettyFunction.find("::");
		size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
		size_t end = prettyFunction.rfind("(") - begin;

		return prettyFunction.substr(begin, end) + "()";
	}

#  define PROF_FUNC  Common::methodName(__PRETTY_FUNCTION__)
#elif (_MSC_VER <= 1800)
#  define PROF_FUNC  __FUNCTION__
#else
#  define PROF_FUNC  __func__ /*Should be supported according to the C++11 standard*/
#endif

#define PROF_TIC Common::Profiler::Get().Tic();
#define PROF_TOC Common::Profiler::Get().Toc(PROF_FUNC);
#define PROF_TOC_NAME(a) Common::Profiler::Get().Toc(a);

	/* This Profiler class is a singleton class that works like tic, toc in MATLAB.

	   Tictocs can be nested. The first toc is paired with the last tic.
	   */
	class Profiler
	{
	private:
		// This is like a stack
		std::vector<uint64_t> m_TicTimes; // Start times for profiling function in microseconds
		std::mutex m_Mutex;

		std::stringstream m_ProfileStream;
		std::string m_Profile; // From the last stack

		Profiler(void)
		{

		};

		// You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singleton appearing.
		Profiler(Profiler const&); // Don't Implement
		void operator=(Profiler const&); // Don't implement

	public:
		static Profiler& Get(void)
		{
			static Profiler P; // Instantiated on first use, guaranteed to be destroyed
			return P;
		};

		std::string GetProfile(void)
		{
			m_Mutex.lock();
			std::string Tmp = m_Profile;
			m_Mutex.unlock();

			return Tmp;
		};

		void Tic(void)
		{
#ifndef PROFILER_ON
			return;
#endif
			m_TicTimes.push_back(Common::getCurrentEpochTime());
		};

		void Toc(std::string FuncName)
		{
#ifndef PROFILER_ON
			return;
#endif
			if (m_TicTimes.size() == 0)
				return;

			uint64_t TOC = Common::getCurrentEpochTime();
			uint64_t TIC = m_TicTimes.back();
			int StackLevel = m_TicTimes.size(); // For nesting display that controls how much space to print before
			std::string DispName;
			for (int kk = 1; kk <= StackLevel && StackLevel > 1; ++kk)
			{
				if (kk == StackLevel)
				{
					DispName += " ";
					break;
				}
				DispName += "-";
			}

			DispName += FuncName;
			DispName.resize(64, ' '); // If smaller, gaps are filled with space. If large, they are truncated.
			m_ProfileStream << DispName << "- " << std::fixed << std::setw(5) << std::setprecision(1) << VPFloat(TOC - TIC) * 0.001 << " ms" << std::endl;

			m_TicTimes.pop_back();

			if (m_TicTimes.size() == 0)
			{
				std::string Line;
				m_Mutex.lock();
				auto Tokens = Common::tokenize(m_ProfileStream.str(), '\n');
				m_Profile = "";
				for (int jj = Tokens.size() - 1; jj >= 0; --jj) // Print in reverse order from stack
					m_Profile += Tokens[jj] + "\n";
				
				//m_Profile = m_ProfileStream.str(); // Simple print
				m_Mutex.unlock();
#ifdef PROFILE_STDOUT
				std::cout << << "[ PROF ]:\n" << m_Profile;
#endif
				m_ProfileStream.str(std::string());
			}
		};
	};

	// Convenience class for profiling functions
	// Put this in the beginning of functions: Common::FuncProfiler prof(PROF_FUNC);
	class FuncProfiler
	{
	private:
		std::string m_FuncName;
	public:
		FuncProfiler(const std::string FuncName = "Unknown::Unknown()")
		{
			m_FuncName = FuncName;
			PROF_TIC;
		};

		~FuncProfiler(void)
		{
			PROF_TOC_NAME(m_FuncName);
		};
	};
} // namespace Common
