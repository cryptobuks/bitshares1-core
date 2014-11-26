#pragma once
#include <stdint.h>
#include <bts/blockchain/types.hpp>
#include <bts/blockchain/condition.hpp>
#include <fc/io/enum_type.hpp>

namespace bts { namespace blockchain {

    enum obj_type
    {
        normal_object = 0,
        account_object = 1,
        asset_object = 2,
        edge_object = 3
    };

    typedef uint64_t object_id_type;

    struct object_record
    {
        object_id_type                _id;
        uint64_t                      short_id()const;
        obj_type                      type()const;

        object_record() {}
        virtual ~object_record() {}
        object_record( const object_id_type& id ):_id(id){}
        object_record( const obj_type& type, const uint64_t& id )
        {
            this->set_id( type, id );
        }

        void                        set_id( obj_type type, uint64_t number );

        variant                     user_data; // user-added metadata for all objects - actual application logic should go in derived class

        // always use chain_interface->get_object_owners(obj)  instead of accessing this!
        // At least until we migrate all legacy object types
        multisig_condition          _owners;

    };

    typedef optional<object_record> oobject_record;

} } // bts::blockchain

FC_REFLECT_ENUM( bts::blockchain::obj_type, (normal_object)(account_object)(asset_object)(edge_object) );
FC_REFLECT( bts::blockchain::object_record, (_id)(user_data)(_owners) );
