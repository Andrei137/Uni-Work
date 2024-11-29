import { GraphQLBoolean, GraphQLInt } from 'graphql';
import { deleteEntity, findEntity } from '../../fakeDb.js';

const deleteUserResolver = (_, args) => {
  return deleteEntity('users', args.id);
};

const deleteUserMutation = {
  type: GraphQLBoolean,
  args: {
    id: { type: GraphQLInt }
  },
  resolve: deleteUserResolver
};

export default deleteUserMutation;
