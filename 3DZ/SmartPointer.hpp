/*
 *  SmartPointer.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-01.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_SMARTPOINTER_HPP
#define TDZ_SMARTPOINTER_HPP

#include <stdexcept>
#include <typeinfo>
#include <cassert>

namespace TDZ {

	template <typename T, class Proxy> class SmartPointer;
	
	template <typename T>
	class ResourceProxy {
	protected:
		ResourceProxy() :
			m_count(0)
		{
		}
		
		virtual ~ResourceProxy() {
			assert(m_count == 0);
		}

		virtual int inc() {
			return ++m_count;
		}
		
		virtual int dec() {
			assert(m_count != 0);
			return --m_count;
		}
		
		virtual T* get() = 0;
		virtual const T* get() const = 0;

		int m_count;

		friend class SmartPointer<T, ResourceProxy<T> >;
	};

	template <typename T>
	class PointerProxy : public ResourceProxy<T> {
	private:
		explicit PointerProxy(T* pointee) :
			ResourceProxy<T>(),
			m_pointee(pointee)
		{
			assert(pointee != NULL);
		}
		
		virtual ~PointerProxy() {
			delete m_pointee;
		}

		T* get() {
			return m_pointee;
		}
		
		const T* get() const {
			return m_pointee;
		}

		T* const m_pointee;

		friend class SmartPointer<T, PointerProxy<T> >;
	};
	
	template <typename T>
	class ArrayProxy : public ResourceProxy<T> {
	private:
		explicit ArrayProxy(T* pointee) :
			ResourceProxy<T>(),
			m_pointee(pointee)
		{
			assert(pointee != NULL);
		}
		
		virtual ~ArrayProxy() {
			delete [] m_pointee;
		}
		
		T* get() {
			return m_pointee;
		}
		
		const T* get() const {
			return m_pointee;
		}
		
		T* const m_pointee;

		friend class SmartPointer<T, ArrayProxy<T> >;
	};

	template <typename T>
	class WeakProxy : public ResourceProxy<T> {
	private:
		explicit WeakProxy(T* pointee) :
			ResourceProxy<T>(),
			m_pointee(pointee)
		{
			assert(pointee != NULL);
		}
		
		explicit WeakProxy(const SmartPointer<T, ResourceProxy<T> > smartPointer) :
			m_pointee(smartPointer.get())
		{
		}
		
		virtual ~WeakProxy() { }
		
		int inc() { return 1; }
		int dec() { return 1; }
		
		T* get() {
			return m_pointee;
		}
		
		const T* get() const {
			return m_pointee;
		}
		
		T* const m_pointee;
		
		friend class SmartPointer<T, WeakProxy<T> >;
	};
	
	template <typename T, class ProxyT>
	class SmartPointer {
	public:
		SmartPointer() :
			m_resourceProxy(NULL)
		{
		}
		
		explicit SmartPointer(T* pointee) :
			m_resourceProxy(pointee ? (new ProxyT(pointee)) : NULL)
		{
			if (m_resourceProxy) {
				m_resourceProxy->inc();
			}
		}
		
		SmartPointer(const SmartPointer<T, ProxyT>& rhs) :
			m_resourceProxy(rhs.m_resourceProxy)
		{
			if (m_resourceProxy) {
				m_resourceProxy->inc();
			}
		}
		
		virtual ~SmartPointer() {
			release();
		}
		
		SmartPointer<T, ProxyT>& operator=(const SmartPointer<T, ProxyT>& rhs) {
			if (rhs.m_resourceProxy) {
				rhs.m_resourceProxy->inc();
			}
			
			release();
			m_resourceProxy = rhs.m_resourceProxy;
			return *this;
		}
		
		operator bool() const {
			return (m_resourceProxy != NULL);
		}
		
		const T* get() const {
			if (m_resourceProxy) {
				return m_resourceProxy->m_pointee;
			}
			throw std::runtime_error(std::string("Trying to dereference smart pointer of type ") + typeid(T).name());
		}
		
		T* get() {

			if (m_resourceProxy) {
				return m_resourceProxy->m_pointee;
			}
			throw std::runtime_error(std::string("Trying to dereference smart pointer of type ") + typeid(T).name());
		}

		operator const T*() const {
			return get();
		}
		
		operator T*() {
			return get();
		}

		const T* operator->() const {
			return reinterpret_cast<const T*>(m_resourceProxy->get());
		}
		
		T* operator->() {
			return reinterpret_cast<T*>(m_resourceProxy->get());
		}
		
		const T& operator*() const {
			return *reinterpret_cast<const T*>(m_resourceProxy->get());
		}
		
		T& operator*() {
			return *reinterpret_cast<T*>(m_resourceProxy->get());
		}
		
		void reset() {
			release();
		}
		
		void reset(T* pointee) {
			release();
			
			if (pointee) {
				m_resourceProxy = new ProxyT(pointee);
				m_resourceProxy->inc();
			}
		}
		
	private:
		void release() {
			if (m_resourceProxy && m_resourceProxy->dec() == 0) {
				delete m_resourceProxy, m_resourceProxy = NULL;
			}
		}
		
		ProxyT* m_resourceProxy;
		
		friend class WeakProxy<T>;
	};
	
	template <typename T, class ProxyT>
	bool operator==(const SmartPointer<T, ProxyT>& lhs, const SmartPointer<T, ProxyT>& rhs)
	{
		if (lhs && rhs) {
			return reinterpret_cast<const T*>(lhs) == reinterpret_cast<const T*>(rhs);
		}
		
		return false;
	}
	
	template <typename T, class ProxyT>
	bool operator!=(const SmartPointer<T, ProxyT>& lhs, const SmartPointer<T, ProxyT>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template <typename T>
	struct SharedPointer {
		typedef SmartPointer<T, PointerProxy<T> > Type;
		
	private:
		SharedPointer();
	};

	template <typename T>
	struct SharedArray {
		typedef SmartPointer<T, ArrayProxy<T> > Type;
		
	private:
		SharedArray();
	};
	
	template <typename T>
	struct WeakPointer {
		typedef SmartPointer<T, WeakProxy<T> > Type;
		
	private:
		WeakPointer();
	};
	
} // TDZ

#endif /* TDZ_SMARTPOINTER_HPP */
