#pragma once

#include <stl/tinystl/unordered_map.h>
#include <stl/tinystl/buffer_base.h>
#include <stl/tinystl/hash.h>
#include <stl/tinystl/hash_base.impl.h>

namespace tinystl {

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>::unordered_map()
		: m_size(0)
	{
		buffer_resize<pointer, Alloc>(m_buckets, 9, 0);
	}

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>::unordered_map(const unordered_map& other)
		: m_size(other.m_size)
	{
#if 0
		const size_t nbuckets = (size_t)(other.m_buckets.last - other.m_buckets.first);
		buffer_resize<pointer, Alloc>(m_buckets, nbuckets, 0);

		for (pointer it = *other.m_buckets.first; it; it = it->next) {
			unordered_hash_node<Key, Value>* newnode = new(placeholder(), Alloc::static_allocate(sizeof(unordered_hash_node<Key, Value>))) unordered_hash_node<Key, Value>(it->first, it->second);
			newnode->next = newnode->prev = 0;

			unordered_hash_node_insert(newnode, hash(it->first), m_buckets.first, nbuckets - 1);
		}
#endif
	}

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>::unordered_map(unordered_map&& other)
		: m_size(other.m_size)
	{
		buffer_move(m_buckets, other.m_buckets);
		other.m_size = 0;
	}

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>::~unordered_map() {
		if (m_buckets.first != m_buckets.last)
			clear();
		buffer_destroy<pointer, Alloc>(m_buckets);
	}

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>& unordered_map<Key, Value, Alloc>::operator=(const unordered_map<Key, Value, Alloc>& other) {
		unordered_map<Key, Value, Alloc>(other).swap(*this);
		return *this;
	}

	template<typename Key, typename Value, typename Alloc>
	inline unordered_map<Key, Value, Alloc>& unordered_map<Key, Value, Alloc>::operator=(unordered_map&& other) {
		unordered_map(static_cast<unordered_map&&>(other)).swap(*this);
		return *this;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::begin() {
		iterator it;
		it.node = *m_buckets.first;
		return it;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::end() {
		iterator it;
		it.node = 0;
		return it;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::begin() const {
		const_iterator cit;
		cit.node = *m_buckets.first;
		return cit;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::end() const {
		const_iterator cit;
		cit.node = 0;
		return cit;
	}

	template<typename Key, typename Value, typename Alloc>
	inline bool unordered_map<Key, Value, Alloc>::empty() const {
		return m_size == 0;
	}

	template<typename Key, typename Value, typename Alloc>
	inline size_t unordered_map<Key, Value, Alloc>::size() const {
		return m_size;
	}

	template<typename Key, typename Value, typename Alloc>
	inline void unordered_map<Key, Value, Alloc>::clear() {
		pointer it = *m_buckets.first;
		while (it) {
			const pointer next = it->next;
			it->~unordered_hash_node<Key, Value>();
			Alloc::static_deallocate(it, sizeof(unordered_hash_node<Key, Value>));

			it = next;
		}

		m_buckets.last = m_buckets.first;
		buffer_resize<pointer, Alloc>(m_buckets, 9, 0);
		m_size = 0;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::find(const Key& key) {
		iterator result;
		result.node = unordered_hash_find(key, m_buckets.first, (size_t)(m_buckets.last - m_buckets.first));
		return result;
	}

	template<typename Key, typename Value, typename Alloc>
	inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::find(const Key& key) const {
		iterator result;
		result.node = unordered_hash_find(key, m_buckets.first, (size_t)(m_buckets.last - m_buckets.first));
		return result;
	}

	template<typename Key, typename Value, typename Alloc>
	inline void unordered_map<Key, Value, Alloc>::rehash(size_t nbuckets) {
		if (m_size + 1 > 4 * nbuckets) {
			pointer root = *m_buckets.first;

			const size_t newnbuckets = ((size_t)(m_buckets.last - m_buckets.first) - 1) * 8;
			m_buckets.last = m_buckets.first;
			buffer_resize<pointer, Alloc>(m_buckets, newnbuckets + 1, 0);
			unordered_hash_node<Key, Value>** buckets = m_buckets.first;

			while (root) {
				const pointer next = root->next;
				root->next = root->prev = 0;
				unordered_hash_node_insert(root, hash(root->first), buckets, newnbuckets);
				root = next;
			}
		}
	}

	template<typename Key, typename Value, typename Alloc>
	inline pair<typename unordered_map<Key, Value, Alloc>::iterator, bool> unordered_map<Key, Value, Alloc>::insert(pair<Key, Value>&& p) {
		pair<iterator, bool> result;
		result.second = false;

		result.first = find(p.first);
		if (result.first.node != 0)
			return result;

		const size_t keyhash = hash(p.first);
		unordered_hash_node<Key, Value>* newnode = new(placeholder(), Alloc::static_allocate(sizeof(unordered_hash_node<Key, Value>))) unordered_hash_node<Key, Value>(static_cast<Key&&>(p.first), static_cast<Value&&>(p.second));
		newnode->next = newnode->prev = 0;

		const size_t nbuckets = (size_t)(m_buckets.last - m_buckets.first);
		unordered_hash_node_insert(newnode, keyhash, m_buckets.first, nbuckets - 1);

		++m_size;
		rehash(nbuckets);

		result.first.node = newnode;
		result.second = true;
		return result;
	}

	template<typename Key, typename Value, typename Alloc>
	inline pair<typename unordered_map<Key, Value, Alloc>::iterator, bool> unordered_map<Key, Value, Alloc>::insert(const pair<Key, Value>& p) {
		//return insert(move(pair<Key, Value>(p)));
		(void)p; return pair<iterator, bool>(); // @todo implement or just remove this function
	}

	template<typename Key, typename Value, typename Alloc>
	inline pair<typename unordered_map<Key, Value, Alloc>::iterator, bool> unordered_map<Key, Value, Alloc>::emplace(pair<Key, Value>&& p) {
		return insert(static_cast<pair<Key, Value>&&>(p));
	}

	template<typename Key, typename Value, typename Alloc>
	inline void unordered_map<Key, Value, Alloc>::erase(const_iterator where) {
		unordered_hash_node_erase(where.node, hash(where->first), m_buckets.first, (size_t)(m_buckets.last - m_buckets.first) - 1);

		where->~unordered_hash_node<Key, Value>();
		Alloc::static_deallocate((void*)where.node, sizeof(unordered_hash_node<Key, Value>));
		--m_size;
	}

	template<typename Key, typename Value, typename Alloc>
	inline void unordered_map<Key, Value, Alloc>::erase(const Key& key) {
		const_iterator where = find(key);
		if(where != end())
			erase(where);
	}

	template<typename Key, typename Value, typename Alloc>
	inline Value& unordered_map<Key, Value, Alloc>::operator[](const Key& key) {
		return insert(pair<Key, Value>(key, Value())).first->second;
	}

	template<typename Key, typename Value, typename Alloc>
	inline void unordered_map<Key, Value, Alloc>::swap(unordered_map& other) {
		size_t tsize = other.m_size;
		other.m_size = m_size, m_size = tsize;
		buffer_swap(m_buckets, other.m_buckets);
	}
}
