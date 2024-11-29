import { JWT_SECRET } from '../../constants.js';
import loginInputType from '../types/loginInputType.js';
import loginResultType from '../types/loginResultType.js';
import jwt from 'jsonwebtoken';
import { findByName } from '../../fakeDb.js';

const loginMutationResolver = (_, args) => {
  const user = findByName(args.credentials.username);

  if (!user) {
    return {
      token: null
    }
  }

  const token = jwt.sign(
    {
      user_id: user.id,
    },
    JWT_SECRET
  );
  return { token };
};

const loginMutation = {
  type: loginResultType,
  args: {
    credentials: { type: loginInputType }
  },
  resolve: loginMutationResolver
};

export default loginMutation;
